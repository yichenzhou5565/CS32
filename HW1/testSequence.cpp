#include <iostream>
#include <cassert>

#include "Sequence.h"

using namespace std;



int main()
{
//    /////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////
//    ///////////////This part of the test case is for std::string/////////////
//    /////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////
//
//
//
//    Sequence s;
//    assert(s.empty());
//    s.insert(0, "a");
//    assert(! s.empty());
//    s.insert(1, "b");
//    s.insert(2, "c");
//    s.insert(3, "b");
//    s.insert(4, "e");
//    //s.dump();
//    assert(s.size() == 5);
//
//    assert(s.insert("A") == 0);
//    assert(s.insert("C") == 1);
//    assert(s.insert("z") == 7);
//    //s.dump();
//
//    assert(s.erase(0));
//    assert(s.erase(0));
//    assert(s.erase(5));
//    //s.dump();
//
//    assert(s.remove("b") == 2);
//    assert(s.size() == 3);
//    //s.dump();
//
//    string x;
//    assert(s.get(0, x)  &&  x == "a");
//    assert(s.get(1, x)  &&  x == "c");
//    assert(s.get(2, x)  &&  x == "e");
//
//    assert(s.set(0, "A") && s.get(0, x) && x == "A");
//    //s.dump();
//    s.set(0, "a");
//
//    assert(s.find("b") == -1);
//    assert(   s.find("a") == 0
//           && s.find("c") == 1
//           && s.find("e") == 2);
//
//    assert(s.size() == 3);
//
//
//    Sequence s1;
//    s1.insert(0, "paratha");
//    s1.insert(0, "focaccia");
//    Sequence s2;
//    s2.insert(0, "roti");
//    s1.swap(s2);
//    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
//               s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
//    //s.dump();
//    //s1.dump();
//    //cerr<<endl;
//    s.swap(s1);
//    //s.dump();
//    //s1.dump();
//    assert(s.size() == 1
//            && s.find("roti") == 0
//            && s.find("a") == -1
//            && s.find("c") == -1
//            && s.find("e") == -1);
//    assert(s1.size() == 3
//           && s1.find("roti") == -1
//           && s1.find("a") == 0
//           && s1.find("c") == 1
//           && s1.find("e") == 2);
//
//
//
//    Sequence t1, t2;
//    t1.insert(0, "C");
//    t1.insert(0, "B");
//    t1.insert(0, "A");
//    t1.insert(3, "D");
////    cerr<<"t1= ";
////    t1.dump();
//
//    t2.insert(0, "b");
//    t2.insert(0, "a");
////    cerr<<"t2= ";
////    t2.dump();
//
//    //cerr<<endl;
//
//    assert(t1.size() == 4);
//    assert(t2.size() == 2);
//    assert(t1.size()>t2.size());
//
//
//
//    //t1.swap(t2);
//    t2.swap(t1);
//    assert(t1.find("a") ==0
//           && t1.find("b") == 1);
//    assert(t2.find("A") ==0
//           && t2.find("B") ==1
//           && t2.find("C") ==2
//           && t2.find("D") ==3);
//    t1.swap(t2);
//    assert(t1.find("A") ==0
//           && t1.find("B") ==1
//           && t1.find("C") ==2
//           && t1.find("D") ==3);
//    assert(t2.find("a") ==0
//           && t2.find("b") == 1);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    /////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////
//    ///////////////This part of the test case is for unsigned long///////////
//    /////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////
//
//
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);




    cerr<<"All tests passed. "<<endl;



    return (0);
}







