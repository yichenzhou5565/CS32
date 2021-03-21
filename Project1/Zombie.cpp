#include "Zombie.h"
#include "Arena.h"

#include <iostream>
#include <cstdlib>
using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////


//constructor method of class zombie
//initialize constructor
Zombie::Zombie(Arena* ap, int r, int c)
: m_arena(ap), m_row(r), m_col(c), m_health(INITIAL_ZOMBIE_HEALTH)
{
    //make sure arena is desirable
    if (ap == nullptr)
    {
        cout << "***** A zombie must be created in some Arena!" << endl;
        exit(1); //error handling
    }
    
    //error handling:
    //out of range values for r and c
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
}

//accessor for rows
int Zombie::row() const
{
    return m_row;
}

//accessor for columns
int Zombie::col() const
{
    return m_col;
}


void Zombie::move()
{
    // Attempt to move in a random direction; if we can not move, do not move
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    
    //move the zombie into a new position, within the arena
    m_arena->determineNewPosition(m_row, m_col, dir);
}


//check if the zombie is still alive
bool Zombie::getAttacked(int dir)  // return true if dies
{
    m_health--;
    if (m_health == 0)
        return true;
    
    //if on the edge position
    if ( ! m_arena->determineNewPosition(m_row, m_col, dir) )
    {
        m_health = 0;
        return true; //zombie dies
    }
    return false;
}
