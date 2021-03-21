#ifndef Arena_h
#define Arena_h



#include "globals.h"
#include "History.h"

class Zombie;
class Player;

class History;

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zombieCount() const;
        //total number of zombies in arena at given time:
        //m_nZombies
    int     numZombiesAt(int r, int c) const;
        //number of zombies at a specific position
    bool    determineNewPosition(int& r, int& c, int dir) const;
        //move the player/zombie into new position
        //true if in the arena but not on the edge position
    void    display() const;
    
    // Mutators
    bool   addZombie(int r, int c);
        //false if number of zombies already reach maximum
    bool   addPlayer(int r, int c);
        //false if a player already exists
    bool   attackZombieAt(int r, int c, int dir);
        //true if the zombie being attacked dies
    bool   moveZombies();
        //true if player still alive
    History& history();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zombie* m_zombies[MAXZOMBIES];
    int     m_nZombies;
    History m_history;
    
};


#endif /* Arena_hpp */
