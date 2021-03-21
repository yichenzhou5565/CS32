#ifndef History_h
#define History_h

#include "globals.h"

class Arena;
class Game;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int n_row, row;
    int n_col, col;
    //Arena* m_arena;
    //Game* m_g;
    int m_counter[MAXROWS][MAXCOLS];
};




#endif
