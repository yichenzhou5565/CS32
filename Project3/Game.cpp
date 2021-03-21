#include <iostream>
#include "Side.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"


Game::Game(const Board& b, Player* south, Player* north)
: m_board(b), mp_south(south), mp_north(north), m_turn(SOUTH)
//    Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
{
    
}


void Game::display() const
//  Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    int hole = m_board.holes();
    
    //print name of north player in the middle of the line
    for (int i=0; i<hole; i++)
        std::cout<<" ";
    std::cout<<mp_north->name()<<std::endl;
    
    //print the number of beans in north holes
    std::cout<<"  ";
    for (int i=1; i<=hole; i++)
    {
        std::cout<<m_board.beans(NORTH, i)<<" ";
    }
    std::cout<<std::endl;
    
    //print number of beans in pot for both north and south
    std::cout<<m_board.beans(NORTH, 0);
    for (int i=0; i<=2*hole; i++)
        std::cout<<" ";
    std::cout<<m_board.beans(SOUTH, 0)<<std::endl;
    
    
    //print number of beans in south holes
    std::cout<<"  ";
    for (int i=1; i<=hole; i++)
    {
        std::cout<<m_board.beans(SOUTH, i)<<" ";
    }
    std::cout<<std::endl;
    
    //print the south player's name in the middle of the line
    for (int i=0; i<hole; i++)
        std::cout<<" ";
    std::cout<<mp_south->name()<<std::endl;
    
    std::cout<<std::endl; //print a new line for cleaness
}


void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    generalStatus(m_board, over, hasWinner, winner);
}

bool Game::move()
{
    if (m_board.beansInPlay(NORTH)==0 || m_board.beansInPlay(SOUTH)==0)
    {
        return false;
    }
    
    generalMove(this, m_board, m_turn, m_turn==SOUTH?mp_south:mp_north); //use general Move
    m_turn = opponent(m_turn); ///give the turn to the other side///
    
    return true;
}


void Game::play()
{
    //if there is no beans in play for south
    this->display();
   
    
    //if there are beans in south
    bool over, hasWinner;
    Side s(SOUTH);
    
    this->status(over, hasWinner, s); //check status
    
    while (over == false) //while the game is not over...
    {
        //if the players are a computers
        //we want to keep it from scrolling crazily fast
        if (mp_south->isInteractive()==false && mp_north->isInteractive()==false)
        {
            std::cout<<"Press enter to continue:";
            std::cin.ignore(100000, '\n');
        }
        this->move();
        this->display();
        this->status(over, hasWinner, s);
        
    }
    
    
    
    //announce the winner, if any
    if (hasWinner==true)
    {
        if (s==SOUTH)
        {
            std::cout<<mp_south->name()<<" wins the game! Congrats!"<<std::endl;
        }
        
        if (s==NORTH)
        {
            std::cout<<mp_north->name()<<" wins the game! Congrats!"<<std::endl;
        }
    }
    else
    {
        std::cout<<"TIE!"<<std::endl;
    }
}


int Game::beans(Side s, int hole) const
{
    if (hole<0 || hole>m_board.holes())
        return (-1);
    return m_board.beans(s, hole); //similiar functionality as the beans in Board...
}
