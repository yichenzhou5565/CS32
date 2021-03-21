//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;

bool somePredicate(string s);


bool allTrue(const string a[], int n)
{
//    if (n<1)
//        return false;
//
//    if ( n==1 )
//    {
//        if ( somePredicate(a[n-1])==false )
//            return false;
//        if ( somePredicate(a[n-1])==true )
//            return true;
//    }
//    if (somePredicate(a[n-1]) == false)
//        return false;
//    return (allTrue(a, n-1));
    
    if (n>=1)
    {
        if (somePredicate(a[0])== false)
            return false;
        else
            return (allTrue(a+1, n-1));
        
    }
    return true;
    
    
}


int countFalse(const string a[], int n)
{
    if (n<1)
        return 0;
    
    if (n==1)
    {
        if (somePredicate(a[0]) == false)
        {
            return 1;
        }
        return 0;
    }
    
    if (somePredicate(a[n-1]) == false)
    {
        return (countFalse(a, n-1)+1);
    }
    return (countFalse(a, n-1));
    
    //return 0;  // This is incorrect.
}


int firstFalse(const string a[], int n)
{
    if (n<1)
        return -1;
    if (n==1)
    {
        if (somePredicate(a[0]) == false)
        {
            return 0;
        }
    }
    
    if (somePredicate(a[n-1]) == true)
    {
        return (firstFalse(a, n-1));
    }
    
    else
    {
        if (firstFalse(a, n-1)==-1)
            return (n-1);
        return (firstFalse(a, n-1));
    }
}


int indexOfLeast(const string a[], int n)
{
    if (n<1)
        return (-1);
    
    if (n==1)
    {
        return 0;
    }
    
    if (a[n-1] < a[indexOfLeast(a, n-1)])
    {
        return (n-1);
    }
    return (indexOfLeast(a, n-1));
}


bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<1 && n2>=1)
        return false;
    if (n2<1)
        return true;
    if (a1[n1-1] == a2[n2-1])
    {
        return (includes(a1, n1-1, a2, n2-1));
    }
    else
    {
        return (includes(a1, n1-1, a2, n2));
    }
}

//int main()
//{
//    string s[]={"12345", "12094","123happy", "happy", "7",
//                "cs32"};
//    string s1[0];
//
//    assert(allTrue(s1, 0) == true);
//
//    assert(allTrue(s, 1) == true);
//    assert(allTrue(s, 2) == true);
//    assert(allTrue(s, 3) == false);
//    assert(allTrue(s, 3) == false);
//    assert(allTrue(s, 4) == false);
//    assert(allTrue(s, 5) == false);
//    assert(allTrue(s, 6) == false);
//
//
//    assert(countFalse(s, 1) == 0);
//    assert(countFalse(s, 2) == 0);
//    assert(countFalse(s, 3) == 1);
//    assert(countFalse(s, 4) == 2);
//    assert(countFalse(s, 5) == 2);
//    assert(countFalse(s, 6) == 3);
//
//
//    assert(firstFalse(s, 1) == -1);
//    assert(firstFalse(s, 2) == -1);
//    assert(firstFalse(s, 3) == 2);
//    assert(firstFalse(s, 6) == 2);
//
//    string t[] = {"H", "Z", "G", "A", "M",
//                  "B"};
//    assert(indexOfLeast(t, 0) == -1);
//    assert(indexOfLeast(t, -10) == -1);
//    assert(indexOfLeast(t, 1) == 0);
//    assert(indexOfLeast(t, 2) == 0);
//    assert(indexOfLeast(t, 3) == 2);
//    assert(indexOfLeast(t, 4) == 3);
//    assert(indexOfLeast(t, 5) == 3);
//    assert(indexOfLeast(t, 6) == 3);
//
//    string t1[] = {"H", "Z", "G"};
//    string t2[] = {"H", "A"};
//    string t3[] = {"H", "G", "Z"};
//    string t4[] = {"H", "H"};
//
//    assert(includes(t, 6, t1, 3) == true);
//    assert(includes(t, 5, t1, 3) == true);
//    assert(includes(t, 4, t1, 3) == true);
//    assert(includes(t, 3, t1, 3) == true);
//    assert(includes(t, 2, t1, 2) == true);
//    assert(includes(t, 2, t1, 3) == false);
//    assert(includes(t, 1, t1, 1) == true);
//    assert(includes(t, 1, t1, 3) == false);
//    assert(includes(t, 0, t1, 3) == false);
//    assert(includes(t, 0, t1, 2) == false);
//    assert(includes(t, 0, t1, 1) == false);
//    assert(includes(t, 0, t1, 0) == true);
//
//    for (int i=0; i<=3; i++)
//    {
//        assert(includes(t, i, t2, 2) == false);
//    }
//
//    for(int i=4; i<=6; i++)
//    {
//        assert(includes(t, i, t2, 2) == true);
//    }
//
//    for (int i=3; i<=6; i++)
//    {
//        assert(includes(t, i, t3, 2) == true);
//        assert(includes(t, i, t3, 1) == true);
//        assert(includes(t, i, t3, 0) == true);
//    }
//
//    for (int i=0; i<=6; i++)
//    {
//        assert(includes(t, i, t3, 3) == false);
//    }
//
//    for (int i=0; i<=6; i++)
//    {
//        assert(includes(t, i, t4, 2) == false);
//        assert(includes(t, 0, t4, 1) == false);
//        assert(includes(t, i, t4, 0) == true);
//        if (i != 0)
//        {
//            assert(includes(t, i, t4, 1) == true);
//        }
//    }
//
//    string spec[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
//    string spec1[] = {"kyle", "kenny", "butters"};
//    string spec2[] = {"kyle", "cartman", "cartman"};
//    string spec3[] = {"kyle", "butters", "kenny"};
//    string spec4[] = {"stan", "kenny", "kenny"};
//
//    includes(spec, 7, spec1, 3);
//    //cout<<spec[6]<<" "<<spec1[2];
//
//    for (int i=0; i<=3; i++)
//    {
//        assert(includes(spec, 7, spec1, i) == true);
//        assert(includes(spec, 7, spec2, i) == true);
//    }
//
//    assert(includes(spec, 7, spec3, 3) == false);
//    assert(includes(spec, 7, spec3, 2) == true);
//    assert(includes(spec, 7, spec3, 1) == true);
//    assert(includes(spec, 7, spec3, 0) == true);
//
//    for (int i=0; i<=7; i++)
//        assert(includes(spec, i, spec4, 3) == false);
//
//    std::cout<<"Passed all tests"<<std::endl;
//
//    return (0);
//}
//
//
//bool somePredicate(string s)
//{
//    for (int i=0; i<s.size(); i++)
//    {
//        if (! isdigit(s[i]))
//            return false;
//    }
//    return true;
//}
//
//

