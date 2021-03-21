#include"ScoreList.h"
#include<cassert>
#include<iostream>
using namespace std;
int main()
{
    ScoreList s;

    assert(s.add(100));
    assert(s.add(98));
    assert(s.add(91));
    assert(s.add(97));
    assert(s.add(78));
    assert(s.add(1));
    assert(s.add(0));
    assert(s.add(1));
    assert(s.add(100));

    assert(s.size() == 9);
    assert(s.maximum() == 100);
    assert(s.minimum() == 0);

    assert(! s.remove(60));
    assert(s.remove(1));
    assert(s.size() == 8);

    assert(s.add(90));
    assert(s.add(91));
    assert(s.size() == 10);

    ScoreList l;

    assert(! l.remove(0) );
    assert(l.maximum() == NO_SCORE);
    assert(l.minimum() == NO_SCORE);

    for (int i=0; i<250; i++)
    {
        assert(l.add(78));
    }

    assert(! l.add(89));
    assert(l.size() == 250);

    assert(l.remove(78));
    assert(l.size() == 249);

    assert(l.add(98));
    assert(l.size() == 250);
    assert(l.maximum() == 98);
    assert(l.minimum() == 78);







    cerr<<"All tests passed. "<<endl;
    return (0);
}


