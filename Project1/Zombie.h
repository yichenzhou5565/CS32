#ifndef Zombie_h
#define Zombie_h

class Arena;

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
        //move zombie randomly into new position in arena
        //dir generated randomly
    bool getAttacked(int dir);
        //true if zombie dies
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Zombie_hpp */
