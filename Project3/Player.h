#ifndef Player_hpp
#define Player_hpp

#include <iostream>
//#include "Side.h"
#include "Board.h"


class Player
{
public:
    Player(std::string name);
    //    Create a Player with the indicated name.
    
    std::string name() const;
    //    Return the name of the player.
    
    virtual bool isInteractive() const;
    //    Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //    Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    
    virtual ~Player();
    //        Since this class is designed as a base class, it should have a virtual destructor.
    
protected:
    virtual bool isLegalMove(const Board &b, int hole) const;
    
private:
    std::string m_name;
    
};


class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    
private:
    int prompt() const;
    
};


class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    
private:
    
};


class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string);
    virtual int chooseMove(const Board& b, Side s) const;
    
private:
    int smartMove(Side s, const Board& b, int& bestHole, int depth=0) const;
    int m_val;
    int m_depth;
    
    
};





#endif
