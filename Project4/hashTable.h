#ifndef hashTable_h
#define hashTable_h

#include <list>
#include <vector>
#include <algorithm>

const int BUCKET = 51; //prime number bucket numbers
//unsigned int hashFunc(const std::string& hashMe);

class hashTable
{
public:
    hashTable() //constructor: initialize everything in table to nullptr
    {
        
        for (int i=0; i<BUCKET; i++)
        {
            table[i]=nullptr;
        }
    }
    
    ~hashTable() //destructor: destruct and set to nullptr
    {
        for (int i=0; i<BUCKET; i++)
        {
            if (table[i] != nullptr)
            {
                delete table[i];
                table[i] = nullptr;
            }
        }
    }
    
    void insert(const std::string& s, const unsigned int& startIndex) //insertion
    {
        int bucket = hashFunc(s);
        Map m(s, startIndex);
        
        if (search(s)==true) //if already exists such a sequence, do nothing and return
            return;
        
        if (table[bucket]==nullptr)
        {
            
            table[bucket] = new std::list<Map>;
            table[bucket]->push_back(m);
        }
        else
        {
            table[bucket]->push_back(m);
            //table[bucket]->insert(table[bucket]->begin(), m);
        }
    }
    
    bool search(const std::string& s)
    {
        int bucket = hashFunc(s);
        if (table[bucket]==nullptr)
            return false;
        if (table[bucket]->size()==0) //if the linked list is empty, no such an item
            return false;
        for (std::list<Map>::iterator itr=table[bucket]->begin();
             itr!=table[bucket]->end(); itr++) //iterate through every entry in the linked list
        {
            if (itr->data == s) //if match found, return true
                return true;
        }
        return false; //if non match found, return false
    }
    
    void getIndex(const std::string& s, int& offset) //get offset
    {
        
        unsigned int bucket = hashFunc(s);
        if (table[bucket]==nullptr) //if no such item in the table...return
            return;
        for (std::list<Map>::iterator itr=table[bucket]->begin();
             itr!=table[bucket]->end(); itr++)
            //iterate through each element corresponding to this bucket
        {
            if (itr->data == s) //if match found
            {
                //empty.push_back(itr->index);
                offset = itr->index; //return its offset
                return; //and return
            }
        }
        
    }
    
    void display() //this is trivial
    //purely for debugging purpose
    {
        for (int i=0; i<BUCKET; i++)
        {
            std::cerr<<i<<": ";
            if (table[i] != nullptr)
            {
                std::cerr<<"("<<table[i]->size()<<") ";
                for (std::list<Map>::iterator itr=table[i]->begin(); itr!=table[i]->end(); itr++)
                {
                    std::cerr<<itr->data<<" ";
                }
            }
            std::cerr<<std::endl; //prints out every element in the bucket, specifying bucket# as well
        }
    }
    
    
    
    
    
private:
    unsigned int hashFunc(const std::string& hashMe)
    {
        std::hash<std::string> str_hash;
        unsigned int hashValue = str_hash(hashMe);
        unsigned int bucketNum = hashValue % BUCKET;
        return bucketNum;
    }
    
    struct Map
    {
        //std::vector<int> index;
        int index;
        std::string data;
        Map(std::string s, int offset) : data(s), index(offset)
        {}
    };
    std::list<Map>* table[BUCKET];
    //std::list<Map>* table;
};


#endif /* hashTable_h */
