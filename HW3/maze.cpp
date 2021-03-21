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

//#include <iostream>
//#include <stack>
//#include <cassert>
//using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

//int main()
//{
//    
//    char maze1[3][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','.','X','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//    
//    
//    assert(pathExists(maze1, 1,1, 1,1));
//    assert(pathExists(maze1, 1,1, 1,2));
//    
//    for (int i=5; i<=10; i++)
//    {
//        assert(! pathExists(maze1, 1,2, 1,i));
//    }
//    
//    char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','.','X','.','.','.','X' },
//        { 'X','.','X','X','.','X','X','X','.','X' },
//        { 'X','X','X','.','.','.','.','X','.','X' },
//        { 'X','.','X','X','X','.','X','X','X','X' },
//        { 'X','.','X','.','.','.','X','.','.','X' },
//        { 'X','.','.','.','X','.','X','.','.','X' },
//        { 'X','X','X','X','X','.','X','.','X','X' },
//        { 'X','.','.','.','.','.','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//    assert (pathExists(maze, 3,5, 8,8));
//    
//    for (int i=1; i<=4; i++)
//    {
//        char maze[10][10] = {
//            { 'X','X','X','X','X','X','X','X','X','X' },
//            { 'X','.','.','.','.','X','.','.','.','X' },
//            { 'X','.','X','X','.','X','X','X','.','X' },
//            { 'X','X','X','.','.','.','.','X','.','X' },
//            { 'X','.','X','X','X','.','X','X','X','X' },
//            { 'X','.','X','.','.','.','X','.','.','X' },
//            { 'X','.','.','.','X','.','X','.','.','X' },
//            { 'X','X','X','X','X','.','X','.','X','X' },
//            { 'X','.','.','.','.','.','.','.','.','X' },
//            { 'X','X','X','X','X','X','X','X','X','X' }
//        };
//        assert (pathExists(maze, 1,1, 1,i));
//    }
//    
//    for (int i=5; i<=9; i++)
//    {
//        char maze[10][10] = {
//            { 'X','X','X','X','X','X','X','X','X','X' },
//            { 'X','.','.','.','.','X','.','.','.','X' },
//            { 'X','.','X','X','.','X','X','X','.','X' },
//            { 'X','X','X','.','.','.','.','X','.','X' },
//            { 'X','.','X','X','X','.','X','X','X','X' },
//            { 'X','.','X','.','.','.','X','.','.','X' },
//            { 'X','.','.','.','X','.','X','.','.','X' },
//            { 'X','X','X','X','X','.','X','.','X','X' },
//            { 'X','.','.','.','.','.','.','.','.','X' },
//            { 'X','X','X','X','X','X','X','X','X','X' }
//        };
//        assert (! pathExists(maze, 1,1, 1,i));
//    }
//    
//    char maze2[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','.','X','.','.','.','X' },
//        { 'X','.','X','X','.','X','X','X','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//    
//    assert(pathExists(maze2, 2, 1, 2, 4));
//    assert(pathExists(maze2, 2,8, 1,6));
//    
//    for (int r=1; r<3; r++)
//    {
//        for (int c=1; c<5; c++)
//        {
//            for (int r1=1; r1<3; r1++)
//            {
//                for (int c1=5; c1<10; c1++)
//                {
//                    char maze2[4][10] = {
//                        { 'X','X','X','X','X','X','X','X','X','X' },
//                        { 'X','.','.','.','.','X','.','.','.','X' },
//                        { 'X','.','X','X','.','X','X','X','.','X' },
//                        { 'X','X','X','X','X','X','X','X','X','X' }
//                    };
//                    assert(! pathExists(maze2, r, c, r1, c1));
//                }
//            }
//        }
//    }
//    cerr<<"Passed all tests."<<endl;
//    
//    return (0);
//}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    //If the start location is equal to the ending location, then we've
    //solved the maze, so return true.
    //Mark the start location as visted.
    //For each of the four directions,
    //If the location one step in that direction (from the start
    //                                            location) is unvisited,
    //then call pathExists starting from that location (and
    //                                                  ending at the same ending location as in the
    //                                                  current call).
    //If that returned true,
    //then return true.
    //Return false.
    
    if (sr==er && sc==ec)
        return true;
    
    maze[sr][sc] = '*';
    
    if (maze[sr-1][sc] != '*' && maze[sr-1][sc] != 'X')
    {
        if (pathExists(maze, sr-1, sc, er, ec))
            return true;
        //return (pathExists(maze, sr-1, sc, er, ec));
    }
    
    if (maze[sr+1][sc] != '*' && maze[sr+1][sc] != 'X')
    {
        if (pathExists(maze, sr+1, sc, er, ec))
            return true;
        //return (pathExists(maze, sr+1, sc, er, ec));
    }
    
    if (maze[sr][sc-1] != '*' && maze[sr][sc-1] != 'X')
    {
        if (pathExists(maze, sr, sc-1, er, ec))
            return true;
        //return (pathExists(maze, sr, sc-1, er, ec));
    }
    
    if (maze[sr][sc+1] != '*' && maze[sr][sc+1] != 'X')
    {
        if (pathExists(maze, sr, sc+1, er, ec))
            return true;
        //return (pathExists(maze, sr, sc+1, er, ec));
    }
    
    return false;
}

