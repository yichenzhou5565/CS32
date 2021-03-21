
#ifndef Side_h
#define Side_h

#include <iostream>
#include <list>

class Board;
class Player;
class Game;

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

int generalMove( Game* g, Board& b, Side& s, const Player* p, int pos=0);
void generalStatus(const Board& m_board, bool& over, bool& hasWinner, Side& winner);



#endif
