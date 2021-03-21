#include <iostream>
#include <cassert>

#include "newSequence.h"

using namespace std;



int main()
{
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    ///////////////This part of the test case is for unsigned long///////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////

    Sequence k(5);
    unsigned long i=2019;
    assert(k.size() == 0);
    assert(k.empty());

    assert(k.insert(0, 25) == 0);
    assert(k.size() == 1);

    assert(k.insert(12) == 0);
    assert(k.insert(13) == 1);
    assert(k.size() == 3);

    assert(k.get(17, i) == false
           && i == 2019);
    assert(k.get(4, i) == false
           && i == 2019);
    assert(k.get(3, i) == false
           && i == 2019);
    assert(k.get(2, i) == true
           && i == 25);
    assert(k.get(1, i) == true
           && i == 13);
    assert(k.get(0, i) == true
           && i == 12);

    assert(k.set(19, 78) == false);
    assert(k.set(3, 78) == false);
    assert(k.get(2, i) == true
           && i == 25);
    assert(k.set(2, 78) == true
           && k.get(2, i) == true
           && i == 78);

    i=2019;

    assert(k.insert(0, 0) == 0);
    assert(k.size() == 4);
    assert(k.insert(4, 26) == 4);
    assert(k.size() == 5);

    assert(k.insert(0, 19) == -1);
    assert(k.insert(0) == -1);

    assert(k.erase(2019) == false);
    //k.dump();
    assert(k.erase(0) == true);
    assert(k.size() == 4);
    //k.dump();
    //should print 12 13 78 26
    assert(k.insert(1, 78) == 1);
    //k.dump();
    //should print 12 78 13 78 26

    assert(k.find(78) == 1);
    assert(k.remove(78) == 2);
    assert(k.find(78) == -1);
    assert(k.remove(78) == 0);
    assert(k.size() == 3);
    //k.dump();
    //should print 12 13 26


    Sequence j(10);
    assert(j.insert(4) == 0);
    assert(j.insert(0) == 0);
    assert(j.insert(1, 1) == 1);
    assert(j.insert(2, 2) == 2);
    assert(j.insert(3) == 3);
    assert(j.size() == 5);
    //j.dump();
    //should print 0 1 2 3 4

    j.swap(k);
    assert(j.size() == 3
           && k.size() == 5);
//    j.dump();
//    k.dump();

    j.swap(k);
    assert(j.size() == 5
           && k.size() == 3);


    //    /////////////////////////////////////////////////////////////////////////
    //    /////////////////////////////////////////////////////////////////////////
    //    ///////////////This part of the test case is for std::string/////////////
    //    /////////////////////////////////////////////////////////////////////////
    //    /////////////////////////////////////////////////////////////////////////
    //
    //
    //
//        Sequence s;
//        assert(s.empty());
//        s.insert(0, "a");
//        assert(! s.empty());
//        s.insert(1, "b");
//        s.insert(2, "c");
//        s.insert(3, "b");
//        s.insert(4, "e");
//        //s.dump();
//        assert(s.size() == 5);
//
//        assert(s.insert("A") == 0);
//        assert(s.insert("C") == 1);
//        assert(s.insert("z") == 7);
//        //s.dump();
//
//        assert(s.erase(0));
//        assert(s.erase(0));
//        assert(s.erase(5));
//        //s.dump();
//
//        assert(s.remove("b") == 2);
//        assert(s.size() == 3);
//        //s.dump();
//
//        string x;
//        assert(s.get(0, x)  &&  x == "a");
//        assert(s.get(1, x)  &&  x == "c");
//        assert(s.get(2, x)  &&  x == "e");
//
//        assert(s.set(0, "A") && s.get(0, x) && x == "A");
//        //s.dump();
//        s.set(0, "a");
//
//        assert(s.find("b") == -1);
//        assert(   s.find("a") == 0
//               && s.find("c") == 1
//               && s.find("e") == 2);
//
//        assert(s.size() == 3);
//
//
//        Sequence s1;
//        s1.insert(0, "paratha");
//        s1.insert(0, "focaccia");
//        Sequence s2;
//        s2.insert(0, "roti");
//        s1.swap(s2);
//        assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
//                   s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
//        //s.dump();
//        //s1.dump();
//        //cerr<<endl;
//        s.swap(s1);
//        //s.dump();
//        //s1.dump();
//        assert(s.size() == 1
//                && s.find("roti") == 0
//                && s.find("a") == -1
//                && s.find("c") == -1
//                && s.find("e") == -1);
//        assert(s1.size() == 3
//               && s1.find("roti") == -1
//               && s1.find("a") == 0
//               && s1.find("c") == 1
//               && s1.find("e") == 2);
//
//
//
//        Sequence t1, t2;
//        t1.insert(0, "C");
//        t1.insert(0, "B");
//        t1.insert(0, "A");
//        t1.insert(3, "D");
//    //    cerr<<"t1= ";
//    //    t1.dump();
//
//        t2.insert(0, "b");
//        t2.insert(0, "a");
//    //    cerr<<"t2= ";
//    //    t2.dump();
//
//        //cerr<<endl;
//
//        assert(t1.size() == 4);
//        assert(t2.size() == 2);
//        assert(t1.size()>t2.size());
//
//
//
//        //t1.swap(t2);
//        t2.swap(t1);
//        assert(t1.find("a") ==0
//               && t1.find("b") == 1);
//        assert(t2.find("A") ==0
//               && t2.find("B") ==1
//               && t2.find("C") ==2
//               && t2.find("D") ==3);
//        t1.swap(t2);
//        assert(t1.find("A") ==0
//               && t1.find("B") ==1
//               && t1.find("C") ==2
//               && t1.find("D") ==3);
//        assert(t2.find("a") ==0
//               && t2.find("b") == 1);
//

    cerr<<"Passed all tests."<<endl;

    return (0);
}











