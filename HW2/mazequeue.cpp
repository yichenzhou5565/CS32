class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

int main()
{
    
    char maze1[3][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    
    assert(pathExists(maze1, 1,1, 1,1));
    assert(pathExists(maze1, 1,1, 1,2));
    
    for (int i=5; i<=10; i++)
    {
        assert(! pathExists(maze1, 1,2, 1,i));
    }
    
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    assert (pathExists(maze, 3,5, 8,8));
    
    for (int i=1; i<=4; i++)
    {
        char maze[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X' },
            { 'X','.','.','.','.','X','.','.','.','X' },
            { 'X','.','X','X','.','X','X','X','.','X' },
            { 'X','X','X','.','.','.','.','X','.','X' },
            { 'X','.','X','X','X','.','X','X','X','X' },
            { 'X','.','X','.','.','.','X','.','.','X' },
            { 'X','.','.','.','X','.','X','.','.','X' },
            { 'X','X','X','X','X','.','X','.','X','X' },
            { 'X','.','.','.','.','.','.','.','.','X' },
            { 'X','X','X','X','X','X','X','X','X','X' }
        };
        assert (pathExists(maze, 1,1, 1,i));
    }
    
    for (int i=5; i<=9; i++)
    {
        char maze[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X' },
            { 'X','.','.','.','.','X','.','.','.','X' },
            { 'X','.','X','X','.','X','X','X','.','X' },
            { 'X','X','X','.','.','.','.','X','.','X' },
            { 'X','.','X','X','X','.','X','X','X','X' },
            { 'X','.','X','.','.','.','X','.','.','X' },
            { 'X','.','.','.','X','.','X','.','.','X' },
            { 'X','X','X','X','X','.','X','.','X','X' },
            { 'X','.','.','.','.','.','.','.','.','X' },
            { 'X','X','X','X','X','X','X','X','X','X' }
        };
        assert (! pathExists(maze, 1,1, 1,i));
    }
    
    char maze2[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    assert(pathExists(maze2, 2, 1, 2, 4));
    assert(pathExists(maze2, 2,8, 1,6));
    
    for (int r=1; r<3; r++)
    {
        for (int c=1; c<5; c++)
        {
            for (int r1=1; r1<3; r1++)
            {
                for (int c1=5; c1<10; c1++)
                {
                    char maze2[4][10] = {
                        { 'X','X','X','X','X','X','X','X','X','X' },
                        { 'X','.','.','.','.','X','.','.','.','X' },
                        { 'X','.','X','X','.','X','X','X','.','X' },
                        { 'X','X','X','X','X','X','X','X','X','X' }
                    };
                    assert(! pathExists(maze2, r, c, r1, c1));
                }
            }
        }
    }
    
//    for (int r=3; r<9; r++)
//    {
//        for (int c=3; c<7; c++)
//        {
//            for (int r1=3; r1<9; r1++)
//            {
//                for (int c1=3; c1<7; c1++)
//                {
//                    char maze3[10][10] = {
//                        { 'X','X','X','X','X','X','X','X','X','X' },
//                        { 'X','.','.','.','.','X','.','.','.','X' },
//                        { 'X','.','X','X','.','X','X','X','.','X' },
//                        { 'X','X','X','.','.','.','.','X','.','X' },
//                        { 'X','.','X','X','X','.','X','X','X','X' },
//                        { 'X','.','X','.','.','.','X','.','.','X' },
//                        { 'X','.','.','.','X','.','X','.','.','X' },
//                        { 'X','X','X','X','X','.','X','.','X','X' },
//                        { 'X','.','.','.','.','.','.','.','.','X' },
//                        { 'X','X','X','X','X','X','X','X','X','X' }
//                    };
//                    assert( pathExists(maze3, r, c, r1, c1) );
//                }
//            }
//        }
//    }
    
    
    cerr<<"Passed all tests."<<endl;
    
    return (0);
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> s;
    Coord start(sr, sc);
    
    s.push(start);
    maze[sr][sc] = '*';
    
    
    while ( ! s.empty() )
    {
        Coord now = s.front();
        //cerr<<now.r()<<" "<<now.c()<<endl;
        s.pop();
        
        if ( now.r() == er && now.c() == ec )
        {
            return true;
        }
        
        int r=now.r(), c=now.c();
        
        if ( maze[r+1][c]!='X' &&  maze[r+1][c]!='*')
        {
            //cout<<"South ";
            Coord newer(r+1, c);
            s.push(newer);
            maze[r+1][c] = '*';
        }
        
        if ( maze[r][c-1]!='X' &&  maze[r][c-1]!='*')
        {
            //cout<<"West ";
            Coord newer(r, c-1);
            s.push(newer);
            maze[r][c-1] = '*';
        }
        
        if ( maze[r-1][c]!='X' &&  maze[r-1][c]!='*')
        {
            //cout<<"North ";
            Coord newer(r-1, c);
            s.push(newer);
            maze[r-1][c] = '*';
        }
        
        if ( maze[r][c+1]!='X' &&  maze[r][c+1]!='*')
        {
            //cout<<"East ";
            Coord newer(r, c+1);
            s.push(newer);
            maze[r][c+1] = '*';
        }
    }
    return false;
}
