#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <functional>
#include <list>
#include <vector>
#include "hashTable.h"
using namespace std;

const int N=16;

//helper funciton: turning digits in a string to int, and set position to the next index
    //after the number returned
int number(const string& s, int& tr)
{
    int result(-1);
    string helper(""); //initialization
    for (; tr<s.size();) //when position , i.e., tr, is wihtin valid range
    {
        while (isspace(s[tr])) //if isspace, proceed onto the next
        {
            tr++;
        }
        while (isdigit(s[tr])) //if it is digit, we add this character to our helper
        {
            helper += s[tr];
            tr++;
        }
        if (helper.empty()==false) //if helper is not empty, then we turn it into int
        {
            result = stoi(helper);
            return result;
        }
        tr++;
    }
    return (-1);
}

//helper function: this is for merging command A
void mergeCommandA(string& s)
{
    int i=0;
    string newer("");
    string helper(""); //initialization
    while (i<s.size())
    {
        int counter = 0;
        if (i+3<s.size() && s[i]=='A'&&s[i+1]=='1'&&s[i+2]==':') //if a valid command A
        {
            newer += "A"; //add A to our newer string
            while (s[i]=='A'&&s[i+1]=='1'&&s[i+2]==':') //while it is valid command
            {
                counter += 1;
                helper += s[i+3];
                i += 4;
            }
            newer += to_string(counter);
            newer += ":";
            newer += helper;
            helper="";
        }
        else //otherwise, just add this character to out newer string
        {
            newer += s[i];
            i++;
        }
    }
    s = newer;
}

void mergeCommandC(string& s)
{
    std::string newer("");
    //loop throught each element of s
    //finaloffset=i, totallength=0;
    //if the element at position i is not C, simply add it to newer
    //if the element at position i is indeed C, go check if this is a command
    //if not a command, simply add it to newer
    //if it is indeed a command
    //use curlength=number(s, i) to get the length
    //s[i] should now be ',', if not, C is not a command
    //if yes, use curoffset=number(s, i) to get the offset
    //then check if s[i] now is C(**)
    //if no, then there is no consecutive commandC, no merging, just add
    //curlength, ',', curoffset to newer
    //if yes, then use number to get newlength, check s[i]==',', get newoffset
    //if curlength+curoffset=newoffset, merging occurs
    //totallength=curlength+newlength
    //curlength=totallength, curoffset unchanged, go back to (**)
    //add to newer
    int i=0;
    while (i<s.size())
    {
        int finaloffset=i, totallength=0;
        if (s[i] != 'C' || !isdigit(s[i+1]))
        {
            newer += s[i];
            i++;
            continue;
        }
        else
        {
            
            
            
            
            newer += "C";
            while (s[i]=='C')
            {
                int curlength=number(s, i);
                if (s[i]!=',')
                {
                    newer += s[i];
                    i++;
                    break;
                }
                int curoffset = number(s, i);
                if (s[i]!='C')
                {
                    newer += (to_string(curlength)+","+to_string(curoffset));
                    break;
                }
                else
                {
                    int newlength=number(s, i);
                    if (s[i]!=',')
                    {
                        newer += s[i];
                        i++;
                        break;
                    }
                    int newoffset=number(s, i);
                    if (curoffset+curlength == newoffset)
                    {
                        totallength = curlength+newlength;
                        finaloffset=curoffset;
                    }
                    if (curoffset+curlength != newoffset)
                    {
                        newer += ("C"+to_string(newlength)+","+to_string(newoffset));
                    }
                }
            }
            if (totallength!=0)
            {
                newer += (to_string(totallength)+","+to_string(finaloffset));
            }
        }
    }
    s = newer;
}

void mergeCommand(string& s)
{
    mergeCommandA(s); //we only use mergeA in here. reaosons explained later in the function creatediff
    //mergeCommandC(s);
}

//we split the sting inputed every N character until end, this is mainly used for operations for fnew
std::string splitbyN(const std::string& s, const int& offset, int& pos)
{
    std::string result(""); //initialization
    if (offset+N >= s.size()) //if we reach the last N charaters, use one parameter argument of substr
    {
        result = s.substr(offset);
        pos = s.size();
        return result;
    }
    result = s.substr(offset, N); //otherwise, use two parameter argument of substr, string class
    //pos += N;
    pos = offset+N; //move along he road
    return result;
}

//this function split the input string into N character sequences, and put them in the hash table
void splitAndInsert(hashTable& t, const std::string& s)
{
    int x=0;
    if (t.search(s)==true)
        return;
    while(x<s.size())
    {
        if (x+N >= s.size())
        {
            t.insert(s.substr(x), x); //if encountering the last few characters
            return;
        }
        t.insert(s.substr(x, N), x); //call insertion member function of class hashTable
        x += 1; //we increment this by 1, not by N, just to make more comprehensive collection of sequences
        //which helps in compressing smaller files significantly
        //experimentally, for warandpeace, if we use N here, the fdiff file would be around 560 bytes
        //but if we use 1 here, it becomes 389 bytes. Wow...
    }
}

bool getInt(istream& inf, int& n) //function from Spec
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset) //Function from Spec
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}


//prototypes...
void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);

void testMergeCommand()
{
    //    string s("C8,0C1,8 helloworldA1:*A1:&");
    //    mergeCommand(s);
    //    cerr<<s<<endl;
    //    assert(s=="C9,0 helloworldA2:*&");
    
    string c("C8,0C2,8C10,1");
    cerr<<c<<endl;
    mergeCommand(c);
    cerr<<c<<endl;
    
    string c1("");
    //std::cerr<<"Passed the test for merging commands."<<std::endl;
}

//test cases...
void primaryTest()
{
    ///Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/
    ifstream greenegg1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggs1.txt");
    ifstream greenegg2("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggs2.txt");
    ofstream diff1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/geDiff.txt");
    createDiff(greenegg1, greenegg2, diff1);
    
    //    greenegg1.seekg(0);
    //
    //    ifstream greeneggDiff("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggDiff.txt");
    //    ofstream greeneggNew("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggNew.txt");
    //    applyDiff(greenegg1, greeneggDiff, greeneggNew);
}

void testSmallMart()
{
    ifstream smallmart1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmart1.txt");
    ifstream smallmart2("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmart2.txt");
    ofstream diff1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmartDiff.txt");
    createDiff(smallmart1, smallmart2, diff1);
}

void testWarAndPeace()
{
    ifstream wAndP1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeace1.txt");
    ifstream wAndP2("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeace2.txt");
    ofstream diff1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeaceDiff.txt");
    createDiff(wAndP1, wAndP2, diff1);
}

void testStrange()
{
    ifstream strange1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strange1.txt");
    ifstream strange2("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strange2.txt");
    ofstream diff1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strangeDiff.txt");
    createDiff(strange1, strange2, diff1);
}


bool runTestSpec1(string oldName, string newName, string diffName, string newName2)
{
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    createDiff(oldFile, newFile, diffFile);
    diffFile.close();
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(applyDiff(oldFile, diffFile2, newFile2));
    newFile2.close();
    
    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        
        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    return true;
}

void runtestSpec2(string oldtext, string newtext)
{
    istringstream oldFile(oldtext);
    istringstream newFile(newtext);
    ostringstream diffFile;
    createDiff(oldFile, newFile, diffFile);
    string result = diffFile.str();
    cout << "The diff file length is " << result.size()
    << " and its text is " << endl;
    cout << result << endl;
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the stream
    istringstream diffFile2(result);
    ostringstream newFile2;
    assert(applyDiff(oldFile, diffFile2, newFile2));
    //std::cerr<<"***"<<newFile2.str()<<"***"<<endl;
    //std::cerr<<"***"<<newtext<<"***"<<endl;
    assert(newtext == newFile2.str());
}


int main()
{
    
    //primaryTest();
    //testMergeCommand();
    //testSmallMart();
    //testWarAndPeace();
    //    testStrange();
    
    runTestSpec1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggs1.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggs2.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggDiff.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/greeneggsNew.txt");
    runTestSpec1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeace1.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeace2.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeaceDiff.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/warandpeaceNew.txt");
    runTestSpec1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strange1.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strange2.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strangeDiff.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/strangeNew.txt");
    runTestSpec1("/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmart1.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmart2.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmartDiff.txt",
                 "/Users/cindy_zhou/Desktop/CS 32/Projects/Project4/p4test/smallmartNew.txt");
    
    
    runtestSpec2("There's a bathroom on the right.",
                 "There's a bad moon on the rise.");
    
    runtestSpec2("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
                 "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
    
    
    return (0);
}

//this is the crucial part of implementations
void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    std::string old(""), cur("");
    std::string diff("");//initialization
    char c_old, c_cur;
    while (fold.get(c_old)) //get fold file into the string old
    {
        old += c_old;
    }
    while (fnew.get(c_cur)) //get fnew into the string cur
    {
        cur += c_cur;
    }
    
    std::string cur_sub(""); //initialization
    int offset=0, pos=0, matchLen=0;
    hashTable t;
    
    ////now split the old (string) into words and insert them into the hash table
    splitAndInsert(t, old);
    
    while (offset < cur.size())
    {
        matchLen = 0;
        cur_sub = splitbyN(cur, offset, pos); //split the new's string
        if (t.search(cur_sub)==true) //if such a sequence exists in the old version
        {
            matchLen += cur_sub.size();
            offset = pos;
            int temp(-1);
            t.getIndex(cur_sub, temp); //get the index, or offset equivalently, of the match
            int tr=temp+cur_sub.size();
            while (tr<old.size()&&pos<cur.size())
            {
                while (old[tr]==cur[pos]) //check character by character after the end of the sequence
                    //in case there are futher matches
                {
                    matchLen++;
                    tr++;
                    pos++;
                }
                offset=pos; //set offset to pos for further loops
                break;
            }
            
            
            diff += ("C"+to_string(matchLen)+","+to_string(temp)); //write command
            
            //pos += matchLen;
            //continue;
        }
        else
        {
            char ch=cur[offset]; //if not found, write the A command
            diff += "A1:";
            diff += ch;
            offset += 1;
            //pos += 1;
            pos = offset;
            //continue;
        }
    }
    //now merge the commands if possible
    mergeCommand(diff); //merge command
    //notice because we checked character by character after the match found,
        //we will not encounter cases such that further merging command C is possible
        //so actually, merging the command is all about merging command A
    
    //put the string diff into the output file fdiff
    fdiff<<diff;
}


bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    std::string old("");
    std::string cur("");
    char c_old; //initialization
    while (fold.get(c_old))
    {
        old += c_old;
    }
    
    char command;
    int length(0), offset(0);
    string add("");
    string sub("");
    
    
    //// follow the commands to create the new file
    
    for (;;) //infinite loop
    {
        bool valid = getCommand(fdiff, command, length, offset);
        if (valid==false)
            return false; //error handling...
        else
        {
            switch (command)
            {
                case 'x':
                    return true; //if end of the entire process
                    break;
                case 'A': //if encounter command A
                    if (length<1)
                        return false;
                    for (int i=0; i<length; i++)
                    {
                        char ch;
                        fdiff.get(ch);
                        add += ch; //just put everything we want to add in this string
                    }
                    fnew<<add; //and output the string into our fnew...
                    add=""; //re-initializa the string
                    break;
                case 'C': //if encounter command C
                    if (offset<0 || offset>=old.size() || length<1 || length>old.size())
                        return false;
                    sub = old.substr(offset, length); //get the old string's appropriate sub
                    fnew<<sub; //and output the sub string into the new file
                    break;
            }
        }
    }
    return true;
}



