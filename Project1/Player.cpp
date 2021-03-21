#include "Player.h"
#include "Arena.h"

#include <iostream>
#include <cstdlib>

using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

//constructor method for the class Player
//initialization:
Player::Player(Arena* ap, int r, int c)
: m_arena(ap), m_row(r), m_col(c), m_age(0), m_dead(false)
{
    //make sure arena is desirable
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1); //error handling
    }
    
    //make sure r and c have desirable values
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
}

//accessor for row
int Player::row() const
{
    return m_row;
}

//accessor for columns
int Player::col() const
{
    return m_col;
}

//accessor for the player's age
//or number of steps
int Player::age() const
{
    return m_age;
}

//if the player stand still (does not move), add 1 to his age
void Player::stand()
{
    m_age++;
}

//if the player chooses to move
void Player::moveOrAttack(int dir)
{
    //add 1 to his age
    m_age++;
    
    
    int r = m_row;
    int c = m_col;
    
    //if not in the edge of arena
    if (m_arena->determineNewPosition(r, c, dir))
    {
        //a zombie exists in the new position
        if (m_arena->numZombiesAt(r, c) > 0)
            //player attacks zombie for once
            m_arena->attackZombieAt(r, c, dir);
        
        //no zombie in the new position
        //the player moves
        else
        {
            m_row = r;
            m_col = c;
        }
    }
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}
