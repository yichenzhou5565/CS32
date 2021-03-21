#include <iostream>
#include <list>
#include <limits>
#include <cassert>

#include "Side.h"
#include "Board.h"
#include "Player.h"
#include "Game.h"

using namespace std;
int main()
{
    Board b(3, 2); //construct board

    BadPlayer p1("bad");
    HumanPlayer p2("M");

    //Game k(b, &p1, &p2);
    //k.play();

    //test to make sure the constructor is doing what it should do...
    assert (b.holes() == 3);
    assert(b.beans(NORTH, 0) == 0); //test pot
    assert(b.beans(SOUTH, 0) == 0);
    for (int i=1; i<=3; i++) //test other = holes
    {
        assert(b.beans(NORTH, i)==2);
        assert(b.beans(SOUTH, i)==2);
    }

    assert(b.beansInPlay(NORTH) == 6); //test beans in play for both sides
    assert(b.beansInPlay(SOUTH) == 6);

    assert(b.totalBeans() == 12); //test total beans


    Side s = NORTH;
    int h = 10;

    //test for "invalid" arguments for sow
        //and make sure it is not chaning anything
    assert(b.sow(NORTH, 0, s, h) == false
           && s==NORTH
           && h==10);
    assert(b.sow(SOUTH, 0, s, h) == false
           && s==NORTH
           && h==10);

    assert(b.sow(NORTH, -1, s, h) == false
           && s==NORTH
           && h==10);
    assert(b.sow(SOUTH, -10, s, h) == false
           && s==NORTH
           && h==10);

    //test for sow
        //"valid" arguments

    //test boundary case for NORTH
    assert(b.sow(NORTH, 1, s, h) == true
           && s==SOUTH
           && h==1
           );//cout<<h<<endl;
    assert(b.beansInPlay(NORTH) == 4);
    assert(b.beansInPlay(SOUTH) == 7);
    assert(b.totalBeans() == 12);
    assert(b.beans(NORTH, 0) == 1
           && b.beans(NORTH, 1) == 0
           && b.beans(NORTH, 2) == 2
           && b.beans(NORTH, 3) == 2);
    assert(b.beans(SOUTH, 0) == 0
           && b.beans(SOUTH, 1) == 3
           && b.beans(SOUTH, 2) == 2
           && b.beans(SOUTH, 3) == 2);

    //test boundary case for SOUTH
    assert(b.sow(SOUTH, 3, s, h) == true
           && s == NORTH
           && h == 3);
    assert(b.beansInPlay(NORTH) == 5);
    assert(b.beansInPlay(SOUTH) == 5);
    assert(b.totalBeans() == 12);
    assert(b.beans(NORTH, 0) == 1
           && b.beans(NORTH, 1) == 0
           && b.beans(NORTH, 2) == 2
           && b.beans(NORTH, 3) == 3);
    assert(b.beans(SOUTH, 0) == 1
           && b.beans(SOUTH, 1) == 3
           && b.beans(SOUTH, 2) == 2
           && b.beans(SOUTH, 3) == 0);

    //test normal case for SOUTH
    assert(b.sow(SOUTH, 1, s, h)==true
           && s==SOUTH
           && h==0
           );
    assert(b.beansInPlay(NORTH) == 5);
    assert(b.beansInPlay(SOUTH) == 4);
    assert(b.totalBeans() == 12);
    assert(b.beans(NORTH, 0) == 1
           && b.beans(NORTH, 1) == 0
           && b.beans(NORTH, 2) == 2
           && b.beans(NORTH, 3) == 3);
    assert(b.beans(SOUTH, 0) == 2
           && b.beans(SOUTH, 1) == 0
           && b.beans(SOUTH, 2) == 3
           && b.beans(SOUTH, 3) == 1);

    //test normal case fro NORTH
    assert(b.sow(NORTH, 2, s, h) == true
           && s==NORTH
           && h==0);
    assert(b.beansInPlay(NORTH) == 4);
    assert(b.beansInPlay(SOUTH) == 4);
    assert(b.totalBeans() == 12);
    assert(b.beans(NORTH, 0) == 2
           && b.beans(NORTH, 1) == 1
           && b.beans(NORTH, 2) == 0
           && b.beans(NORTH, 3) == 3);
    assert(b.beans(SOUTH, 0) == 2
           && b.beans(SOUTH, 1) == 0
           && b.beans(SOUTH, 2) == 3
           && b.beans(SOUTH, 3) == 1);

    //test "invalid" arguments for setBeans
    assert(b.setBeans(NORTH, 1, -1) == false);
    assert(b.setBeans(NORTH, -1, 12) == false);
    assert(b.setBeans(NORTH, 4, 12) == false);



    BadPlayer badpl("BadComputer"); //create players
    BadPlayer bp("BAD");
    HumanPlayer hp("Me");

    //    Game g3(b, &badpl, &bp);
    //    g3.play();

    //test game and display function
    Game g(b, &badpl, &hp);
    //    g.display();

    //g.play();

    bool over(true), hasWinner(true);
    s=NORTH;

    //g.display();

    //test status: not over case
    g.status(over, hasWinner, s);
    assert(over==false
           && hasWinner==true
           && s==NORTH);

    assert(b.setBeans(NORTH, 3, 0) == true
           && b.setBeans(NORTH, 1, 0) == true
           && b.setBeans(SOUTH, 2, 0) == true
           && b.setBeans(SOUTH, 3, 0) == true);

    //test game for humanplayer versus bad player
    Game g1(b, &badpl, &hp);

    //test status: over but tie
    g1.status(over, hasWinner, s);
    assert(over==true
           && hasWinner==false
           && s==NORTH);

    //test setbeans
    assert(b.setBeans(SOUTH, 0, 18)==true);
    Game g2(b, &badpl, &hp);
    g2.status(over, hasWinner, s);

    //test for status: over, has a winner
    assert(over==true
           && hasWinner==true
           && s==SOUTH);
    //g2.display();

    ////test for badplayer versus smart player case
    SmartPlayer sp("Smartty");
    Board b2(4, 3);
    Game g4(b2, &badpl, &sp);
    Game g5(b2, &hp, &sp);
    //g5.play();

    //g4.display();

    //g4.play();

    ////test for six holes case
    Board b3(6, 2);
    Game g6(b3, &sp, &hp);
    Game g7(b3, &sp, &hp);

    g6.play();


    //test the case of circulating several times for sow
    Board b4(1, 4);
    assert(b4.sow(SOUTH, 1, s, h)==true
           && s==SOUTH
           && h==0);
    assert(b4.beans(SOUTH, 0)==2
           && b4.beans(SOUTH, 1)==1
           && b4.beans(NORTH, 0)==0
           && b4.beans(NORTH, 1)==5);

    //test interactive for Player..
    assert(bp.isInteractive()==false);
    assert(sp.isInteractive()==false);
    assert(hp.isInteractive()==true);
    assert(badpl.isInteractive()==false);

    //test name for player
    assert(hp.name()=="Me");
    assert(sp.name()=="Smartty");
    assert(badpl.name()=="BadComputer");


    std::cerr<<"Passed all tests."<<endl;
    return (0);
}








int generalMove( Game* g, Board& b, Side& s, const Player* p, int pos)
{
    
    bool cont = true; //should we continue this move?
    
    while (cont == true) //while we haven't finished this complete move...
    {
        //if no other moves possible..
        //which means there is no beansInPlay
        //or one of the player's pot has more than half of all beans
        //we will simply return positive or negative infinity accordingly
        int northPot= b.beans(NORTH, 0);
        int southPot= b.beans(SOUTH, 0);
        
        Side es(SOUTH);
        int eh(0);
        
        int totalBeans= b.totalBeans();
        //cout<<b.beansInPlay(s)<<" "<<b.beansInPlay(opponent(s))<<endl;
        
        if (g==nullptr && (b.beansInPlay(s)==0||b.beansInPlay(opponent(s))==0 || 2*northPot > totalBeans || 2*southPot > totalBeans))
        {
            return (northPot>southPot) ? numeric_limits<int>::min() : numeric_limits<int>::max();
        }
        
        //now we want to decide to which position we are going to move to
        int cPos;
        if (pos!=0) //if not default, cPos is whatever is given
        {
            cPos = pos;
        }
        else
        {
            cPos = p->chooseMove(b, s); //otherwise, choose the position through chooseMove
        }
        
        b.sow(s, cPos, es, eh); //now sow the beans with the position from last statement
        
        ////CASE #1: end up in his own pot, do another sow: no change for cont
        if (eh==0&&es==s)
        {
            cPos=0;
            pos=0;
            if (g!=nullptr)
                g->display();
            //return -9;
            continue;
        }
        
        
        ////CASE #2: capture or regular end
        else
        {
            cont = false; //set cont to false to end this turn
            if (eh>0 && b.beans(s, eh)==1 && b.beans(opponent(s), eh)!=0 && es==s)
                ////if nothing at the opponent's array////capture
            {
                b.moveToPot(opponent(s), eh, s);
                b.moveToPot(s, eh, s);
            }
        }
        
        ////Now decide if the game is over
        ////the idea is that when the game is over, we should move everything into the pot
        bool over(false), hasWinner(false);
        Side winner(SOUTH);
        
        generalStatus(b, over, hasWinner, winner);
        
        if (over == true)
//            (b.beans(NORTH, 0) > totalBeans/2
//            || b.beans(SOUTH, 0) > totalBeans/2)
        {
            cont = false; //do not continue anymore
            
            for (int i=1; i<=b.holes(); i++)
            {
                if (b.beans(NORTH, i)!=0)
                {
                    b.moveToPot(NORTH, i, NORTH); //move everything in north to northPot
                }
                if (b.beans(SOUTH, i)!=0)
                {
                    b.moveToPot(SOUTH, i, SOUTH); //move everything in south to southPot
                }
            }
            if (g!=nullptr)
                g->display();
        }
    }
    return 0;
}



void generalStatus(const Board& m_board, bool& over, bool& hasWinner, Side& winner)
{
    
    int northPot(0), southPot(0);
    over = false;
    northPot = m_board.beans(NORTH, 0);
    southPot = m_board.beans(SOUTH, 0);
    
    
    
    
    
    if (m_board.beansInPlay(NORTH)!=0 && m_board.beansInPlay(SOUTH)!=0)
    {
        over = false;
        return;
    }
    
    over = true;
    
//    if (northPot>m_board.totalBeans()/2)
//    {
//        over = hasWinner = true;
//        winner = NORTH;
//        return;
//    }
//
//    if (southPot>m_board.totalBeans()/2)
//    {
//        over = hasWinner = true;
//        winner = SOUTH;
//        return;
//    }
    
    if (northPot == southPot)
    {
        hasWinner=false;
        return;
    }
    
    
    
    else
    {
        hasWinner = true;
        winner = (northPot>southPot) ? NORTH:SOUTH;
    }
}
