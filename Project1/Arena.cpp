#include "Arena.h"
#include "Player.h"
#include "Zombie.h"
#include "History.h"

#include <cstdlib>
#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////



//initialization of constructor call to Arena
Arena::Arena(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols), m_player(nullptr), m_nZombies(0), m_history(nRows,nCols)
{
    //error handling:
    //make sure that rows and columes are within the allowed size
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
}

//destructor of Arena
Arena::~Arena()
{
    //loop to destruct every element
    for (int k = 0; k < m_nZombies; k++)
        delete m_zombies[k];
    delete m_player;
}

//accessor for rows
int Arena::rows() const
{
    return m_rows;
}

//accesor for columns
int Arena::cols() const
{
    return m_cols;
}

//accessor for player in the arena
Player* Arena::player() const
{
    return m_player;
}

//accessor for the number of zombies in the arena in the beginning
int Arena::zombieCount() const
{
    return m_nZombies;
}

//accessor for number of zombies at a specific position in the arena
int Arena::numZombiesAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nZombies; k++)
    {
        const Zombie* zp = m_zombies[k];
        if (zp->row() == r  &&  zp->col() == c)
            count++;
    }
    return count;
}


//mutator implementation for moving into a new position
bool Arena::determineNewPosition(int& r, int& c, int dir) const
{
    switch (dir)
    {
            //error handling:
            //make sure that player/zombie will not be moved out of arena after moving
            //then we can do the operations by adding/subtracting 1 onto row/columns
        case UP:     if (r <= 1)      return false; else r--; break;
        case DOWN:   if (r >= rows()) return false; else r++; break;
        case LEFT:   if (c <= 1)      return false; else c--; break;
        case RIGHT:  if (c >= cols()) return false; else c++; break;
        default:     return false;
    }
    return true;
}

void Arena::display() const
{
    // Position (row,col) of the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each zombie's position
    for (int k = 0; k < m_nZombies; k++)
    {
        const Zombie* zp = m_zombies[k];
        char& gridChar = grid[zp->row()-1][zp->col()-1];
        switch (gridChar)
        {
            case '.':  gridChar = 'Z'; break;
            case 'Z':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
        }
    }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there is also a zombie there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, zombie, and player info
    cout << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addZombie(int r, int c)
{
    // Dynamically allocate a new Zombie and add it to the arena
    if (m_nZombies == MAXZOMBIES)
        return false;
    m_zombies[m_nZombies] = new Zombie(this, r, c);
    m_nZombies++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

bool Arena::attackZombieAt(int r, int c, int dir)
{
    // Attack one zombie.  Returns true if a zombie was attacked and destroyed,
    // false otherwise (no zombie there, or the attack did not destroy the
    // zombie).

    //initialize k to 0
    int k = 0;
    for ( ; k < m_nZombies; k++)
    {
        //if zombie is being attacked
        if (m_zombies[k]->row() == r  &&  m_zombies[k]->col() == c)
            break;
    }
    if (k < m_nZombies  &&  m_zombies[k]->getAttacked(dir))  // zombie dies
    {
        delete m_zombies[k]; //the zombie dies, so delete it
        m_zombies[k] = m_zombies[m_nZombies-1];
        m_nZombies--; //one zombie died, so number of zombies decreases by 1



        m_history.record(m_player->row(), m_player->col());




        return true;
    }
    return false;
}








bool Arena::moveZombies()
{
    //loop to move every zombie in the arena
    for (int k = 0; k < m_nZombies; k++)
    {
        Zombie* zp = m_zombies[k];
        
        //move zombie randomly through member function move
        zp->move();
        
        //if the zombie bump into player
        if (zp->row() == m_player->row()  &&  zp->col() == m_player->col())
            //player dies
            m_player->setDead();
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

History& Arena::history()
{
    return m_history;
}
