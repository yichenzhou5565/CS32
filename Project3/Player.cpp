#include "Player.h"
#include "Board.h"

#include <limits>
#include <cmath>
#include <map>

Player::Player(std::string name) : m_name(name)
{
    
}


std::string Player::name() const //trivial
{
    return m_name;
}


bool Player::isInteractive() const //trivial
{
    return false;
}

bool Player::isLegalMove(const Board& b, int hole) const //trivial
{
    if (hole<1 || hole>b.holes())
        return false;
    return true;
}


Player::~Player()  {} //base class virtual destructor


HumanPlayer::HumanPlayer(std::string name) : Player(name)
{
    
}

bool HumanPlayer::isInteractive() const //interactive if human
{
    return true;
}


int HumanPlayer::chooseMove(const Board& b, Side s) const
{
//    int hole = this->prompt();
//
//    while ( hole>b.holes() || hole<1 )
//    {
//        hole = this->prompt();
//    }
    
    int hole(0);
    bool over(true), hasWinner(true);
    Side winner(SOUTH);
    
    
    //while the game is not over, prompt...
    do
    {
        hole = this->prompt();
        generalStatus(b, over, hasWinner, winner);
    }
    while (   over==false && (hole<1 || hole>b.holes() || b.beans(s, hole)==0)
           //&& (b.beans(SOUTH, 0)<=b.totalBeans()/2 || b.beans(NORTH, 0)<=b.totalBeans()/2)
           );

    return hole; //return the chosen hole
}


int HumanPlayer::prompt() const //trivial..
{
    int hole(0);
    std::cout<<"Select a hole, "<<name()<<": ";
    std::cin>>hole;
    return hole;
}


BadPlayer::BadPlayer(std::string name) : Player(name) {} //derived class c'tor

int BadPlayer::chooseMove(const Board& b, Side s) const
    ////just choose the hole nearest to pot with >0 beans
{
    int pos = 1;
    
    while (b.beans(s, pos) == 0)
        pos++;
    
    return pos;
}


SmartPlayer::SmartPlayer(std::string name) //d'class c'tor
: Player(name), m_val(0), m_depth(0) {}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int choice(0), d(0);
    
    int est = b.holes()*(b.beansInPlay(SOUTH)+b.beansInPlay(NORTH));
    if (est>=110) //divide into quartiles to that it runs the accurate # of recursions..
    {
        d=1;
    }
    else if (est>=60)
    {
        d=3;
    }
    else if (est>=30)
    {
        d=6;
    }
    else
    {
        d=10;
    }
    
    
    smartMove(s, b, choice, d); //call smartmove function
//    bool over, hasWinner;
//    Side winner;
//    generalStatus(b, over, hasWinner, winner);
    //std::cout<<choice<<std::endl;
    if (choice==0 || b.beans(s, choice)==0)
        return -1;
//    if (over==true)
//        return -1;
    
    return choice;
}

int SmartPlayer::smartMove(Side s, const Board& b, int& bestHole,  int depth) const
{
    //if no move for player exists (i.e., game is over),
    //bestHole = -1
    //value = value of this position (i.e., +∞, -∞, or 0)
    //return
    int val = 0;
    Board temp = b;
    
    int sp =b.beans(SOUTH, 0);
    int np =b.beans(NORTH, 0);
 
    bool over(false), hasWinner(false);
    Side winner(SOUTH);
    
    generalStatus(b, over, hasWinner, winner); //check if the game is over..
    
    ////Base Case 1:
    if ( over==true)  //if the game is over
    {
        //bestHole = -1;
        if (hasWinner==false) //but no winner
            val = sp-np;
        else
        {
            val = (winner==SOUTH)
            ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min(); //return infinity
        }
        return val;
    }
    
    ////Base Case 2:
    //if the criterion says we should not search below this node
    //bestHole = -1
    //value = value of this position
    //return
    if (depth<=0)
    {
        //bestHole = -1;
        val = sp-np;
        return val;
    }
    
    ////Base Case 3:
    //no winner yet, but result is set
    if (2*abs(sp-np)>=b.totalBeans() || np>b.totalBeans()/2 || sp>b.totalBeans()/2)
    {
        val = sp>np ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
        return val;
    }
    
    std::map<int, int> m;
    
    for (int h=0; h<b.holes(); h++)
    {
        if(temp.beans(s, h+1)!=0)
        {
            int pos=generalMove(nullptr, temp, s, this, h+1);
            int bestpos;
            if (pos==-9)
                bestpos = smartMove(s, temp, bestHole, depth);
            else
            {
                bestpos = smartMove(opponent(s), temp, bestHole, depth-1); //recursion
            }
            temp = b;
            m[bestpos] = h+1; //map the best position to the hole num
        }
    }
    //map automatically sorted...
    std::map<int, int>::iterator itr ;
    if (s==NORTH) //return the smallest
    {
        itr = m.begin();
        val = itr->first;
        bestHole = itr->second;
    }
    else //if s is SOUTH, return the biggest
    {
        itr = m.end();
        itr--;
        val = itr->first;
        bestHole = itr->second;
    }
    return val; //return the best value
}
