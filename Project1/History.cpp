#include "History.h"
//#include "Arena.h"
//#include "Game.h"
#include <iostream>

History::History(int nRows, int nCols)
: n_row(nRows), n_col(nCols)
{
    for (int i=0; i<nRows; i++)
    {
        for (int j=0; j<nCols; j++)
        {
            m_counter[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r>0 && c>0 && r<=n_row && c<=n_col)
    {
        m_counter[r-1][c-1]++;
        row = r;
        col = c;
        return true;
    }
    
    return false;
}


void History::display() const
{
    
    
    //write history grid
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    char letter;
    
    
    // Fill the grid with dots
    for (r = 0; r < n_row; r++)
    {
        for (c = 0; c < n_col; c++)
        {
            switch (m_counter[r][c])
            {
                case 0: letter = '.'; break;
                case 1: letter = 'A'; break;
                case 2: letter = 'B'; break;
                case 3: letter = 'C'; break;
                case 4: letter = 'D'; break;
                case 5: letter = 'E'; break;
                case 6: letter = 'F'; break;
                case 7: letter = 'G'; break;
                case 8: letter = 'H'; break;
                case 9: letter = 'I'; break;
                case 10:letter = 'J'; break;
                case 11:letter = 'K'; break;
                case 12:letter = 'L'; break;
                case 13:letter = 'M'; break;
                case 14:letter = 'N'; break;
                case 15:letter = 'O'; break;
                case 16:letter = 'P'; break;
                case 17:letter = 'Q'; break;
                case 18:letter = 'R'; break;
                case 19:letter = 'S'; break;
                case 20:letter = 'T'; break;
                case 21:letter = 'U'; break;
                case 22:letter = 'V'; break;
                case 23:letter = 'W'; break;
                case 24:letter = 'X'; break;
                case 25:letter = 'Y'; break;
                default:letter = 'Z'; break;
                    
            }
            
            grid[r][c] = letter;
        }
    }
    
    clearScreen();
    for (r = 0; r < n_row; r++)
    {
        for (c = 0; c < n_col; c++)
            std::cout << grid[r][c];
        std::cout << std::endl;
    }
    
    //write an empty line
    std::cout<<std::endl;
    
    
}
