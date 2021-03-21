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
#include <stack>
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
    
    cerr<<"Passed all tests."<<endl;
    
    return (0);
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> s;
    Coord start(sr, sc);
    
    s.push(start);
    maze[sr][sc] = '*';
    
    
    while ( ! s.empty() )
    {
        Coord now = s.top();
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
