#include "Game.h"

#include <iostream>
#include <cstdlib>

#include "Player.h"
#include "Zombie.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////


//constructor method for the class Game
Game::Game(int rows, int cols, int nZombies)
{
    //make sure the number of zombies in the arena is desirable
    if (nZombies < 0)
    {
        cout << "***** Cannot create Game with negative number of zombies!" << endl;
        exit(1);
    }
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
        << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }
    
    //make sure there is place to zombies to stay in
    if (rows == 1  &&  cols == 1  &&  nZombies > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the zombies!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with zombies
    while (nZombies > 0)
    {
        //generate random r and c within desirable range
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        
        // Don't put a zombie where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addZombie(r, c);
        nZombies--;
    }
}

Game::~Game()
{
    delete m_arena;
}




void Game::play()
{
    //display arena at first hand
    m_arena->display();
    Player* p = m_arena->player();
    if (p == nullptr)
        return;
    
    //while player is alive and zombies exist
    while ( ! m_arena->player()->isDead()  &&  m_arena->zombieCount() > 0)
    {
        //continue the game
        cout << endl;
        cout << "Move (u/d/l/r//h/q): ";
        
        string action;
        getline(cin,action);
        //cin.ignore(10000, '\n');
        if (action.size() == 0)  // player stands
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->moveOrAttack(decodeDirection(action[0]));
                    m_arena->moveZombies();
                    break;
                case 'h':
                    m_arena -> history().display();
                    //cin.ignore(10000,'\n');
                    cout<<"Press enter to continue.";

                    cin.ignore(10000,'\n');
                    break;
                    //continue;
            }
            
        }
        
        //move zombies randomly
        //m_arena->moveZombies();
        
        //display arena after this round
        m_arena->display();
    }
}

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}
