//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;


int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2<=0)
        return (1);
    if (n1 < n2)
        return 0;
    int counter=0;
    counter = countIncludes(a1+1, n1-1, a2, n2);
    
    if (a1[0] == a2[0])
        return (counter+countIncludes(a1+1, n1-1, a2+1, n2-1));
    return (counter);
    
    
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
              int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > separator
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
//may use seperate
void order(string a[], int n)
{
    if (n <= 1)
        return;
    
    string seperator = a[n/2];
    int firstNotLess, firstGreater;
    
    separate(a, n, seperator, firstNotLess, firstGreater);
    
    if (firstNotLess != n)
        order(a, firstNotLess);
    if (firstGreater != n)
        order(a+firstGreater, n-firstGreater);
}

//int main()
//{
//    string t[] = {"D", "Z", "W", "A", "B", "A"};
//    order(t, 1);
//    assert(t[0] == "D"
//           && t[1] == "Z"
//           && t[2] == "W"
//           && t[3] == "A"
//           && t[4] == "B"
//           && t[5] == "A");
//    order(t, 3);
//    assert(t[0] == "D"
//           && t[1] == "W"
//           && t[2] == "Z"
//           && t[3] == "A"
//           && t[4] == "B"
//           && t[5] == "A");
//    order(t, 6);
//    assert(t[0] == "A"
//           && t[1] == "A"
//           && t[2] == "B"
//           && t[3] == "D"
//           && t[4] == "W"
//           && t[5] == "Z");
//    order(t, 0);
//    assert(t[0] == "A"
//           && t[1] == "A"
//           && t[2] == "B"
//           && t[3] == "D"
//           && t[4] == "W"
//           && t[5] == "Z");
//
//
//    string k[]={"hello", "", "helloWorld"};
//    order(k, 0);
//    assert(k[0] == "hello"
//           && k[1] == ""
//           && k[2] == "helloWorld");
//    order(k, 1);
//    assert(k[0] == "hello"
//           && k[1] == ""
//           && k[2] == "helloWorld");
//    order(k, 3);
//    assert(k[0] == ""
//           && k[1] == "hello"
//           && k[2] == "helloWorld");
//
//
//    string spec[] = {"stan" ,"kyle" ,"cartman" ,"kenny", "kyle", "cartman", "butters"};
//    string spec1[] = {"stan", "kenny", "cartman"};
//    string spec2[] ={ "stan", "cartman", "butters"};
//    string spec3[] = {"kenny", "stan", "cartman"};
//    string spec4[] = {"kyle", "cartman", "butters" };
//
//    assert(countIncludes(spec, 7, spec1, 3) == 1);
//    assert(countIncludes(spec, 7, spec1, 2) == 1);
//    assert(countIncludes(spec, 7, spec1, 1) == 1);
//    assert(countIncludes(spec, 7, spec1, 0) == 1);
//
//    assert(countIncludes(spec, 7, spec2, 3) == 2);
//    assert(countIncludes(spec, 7, spec2, 2) == 2);
//    assert(countIncludes(spec, 7, spec2, 1) == 1);
//    assert(countIncludes(spec, 7, spec2, 0) == 1);
//
//    assert(countIncludes(spec, 7, spec3, 3) == 0);
//    assert(countIncludes(spec, 7, spec3, 2) == 0);
//    assert(countIncludes(spec, 7, spec3, 1) == 1);
//    assert(countIncludes(spec, 7, spec3, 0) == 1);
//
//    assert(countIncludes(spec, 7, spec4, 3) == 3);
//    assert(countIncludes(spec, 7, spec4, 2) == 3);
//    assert(countIncludes(spec, 7, spec4, 1) == 2);
//    assert(countIncludes(spec, 7, spec4, 0) == 1);
//
//    assert(countIncludes(spec, 0, spec1, 0) == 1);
//    assert(countIncludes(spec, 0, spec1, 1) == 0);
//
//    string s[10] = { "333","3330","222","123","1234","123","1234","","123","123435" };
//    string s1[10] = {};
//    string s2[1] = { "333" };
//    string s3[2] = { "222","123" };
//    string s4[3] = { "123","1234" };
//    string s5[4] = { "12314","222","123","234" };
//    string s6[1] = { "2" };
//    string s7[2] = { "1","2" };
//    string s8[3] = { "123","123","" };
//
//    assert(countIncludes(s, 10, s3, 2) == 3);
//    assert(countIncludes(s, 10, s1, 0) == 1);
//    assert(countIncludes(s, 10, s4, 2) == 3);
//    assert(countIncludes(s, 10, s2, 1) == 1);
//    order(s, 10);
//    assert(s[0] == "" &&s[9] == "3330" &&s[1] == "123");
//
//
//    std::cerr<<"Passed all tests."<<std::endl;
//
//}
