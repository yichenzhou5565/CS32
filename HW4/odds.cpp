//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <cassert>
//using namespace std;

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
    if (v.size()<=0)
        return;
    int i=0;
    int size = v.size();
    while (i<size && v.empty()==false)
    {
        while (i<size && v[i] % 2 != 0)
        {
            v.erase(v.begin()+i);
            size--;
        }
        i++;
        //size = v.size();
    }
//    if (v[v.size()-1] % 2 != 0)
//    {
//        v.erase(v.end()-1);
//    }
}
//void test()
//{
//    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
//    vector<int> x(a, a+8);  // construct x from the array
//    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
//    removeOdds(x);
//    assert(x.size() == 4);
//    sort(x.begin(), x.end());
//    int expect[4] = { 2, 4, 6, 8 };
//    for (int k = 0; k < 4; k++)
//        assert(x[k] == expect[k]);
//}
//
//void testSpecial()
//{
//    int a[8] = {1, 3, 15, 19, 12, 2, 4, 18};
//    vector<int> odd(a, a+4);
//    vector<int> even(a+4, a+8);
//    removeOdds(odd);
//    assert(odd.size()==0);
//    assert(odd.empty()==true);
//    removeOdds(even);
//    assert(even.size()==4);
//    sort(even.begin(), even.end());
//    int expect[]={2, 4, 12, 18};
//    for (int i=0; i<4; i++)
//        assert(even[i]==expect[i]);
//}
//
//int main()
//{
//    test();
//    testSpecial();
//    
//    std::cerr<<"Passed all tests."<<std::endl;
//    return 0;
//}
