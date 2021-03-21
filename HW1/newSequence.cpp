
#include "newSequence.h"




//Sequence::Sequence() : m_size(0), max_size(DEFAULT_MAX_ITEMS)
//{
//    m_sequence = new ItemType[max_size];
//}


Sequence::Sequence( const int& value) : max_size(value), m_size(0)
{
    if (value < 0)
    {
        exit (1);
    }
    
    if (value == 0)
    {
        max_size = DEFAULT_MAX_ITEMS;
    }
    m_sequence = new ItemType[max_size];
}


//copy constructor
Sequence::Sequence(const Sequence& other)
{
    
    max_size = other.max_size;
    m_size = other.size();
    
    m_sequence = new ItemType[m_size+1];
    
    for (int i=0; i<other.size(); i++)
    {
        //ItemType temp;
        m_sequence[i] = other.m_sequence[i];
    }
}


Sequence& Sequence::operator=(const Sequence& rhs)
{
    //delete []m_sequence;
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
        
//        m_size = rhs.m_size;
//        max_size = rhs.max_size;
//        for (int i=0; i<max_size; i++)
//        {
//            m_sequence[i] = rhs.m_sequence[i];
//        }
        
    }
    
    return *this;
}


//destructor
Sequence::~Sequence()
{
    delete [] m_sequence;
}


bool Sequence::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}


void Sequence::dump() const
{
    for(int i=0; i<m_size; i++)
    {
        std::cerr<<m_sequence[i]<<" ";
    }
    std::cerr<<std::endl;
}



int Sequence::size() const
{
    return (m_size);
}


int Sequence::insert(int pos, const ItemType& value)
{
    int s=m_size;
    
    if (pos<=s && pos>=0 && s<max_size)
    {
        m_size++;
        for (int i=s-1; i>=pos; i--)
        {
            m_sequence[i+1] = m_sequence[i];
        }
        m_sequence[pos] = value;
        
        return (pos);
    }
    
//    if (pos<=m_size && pos>=0 && m_size<max_size)
//    {
//        for (int i=m_size-1; i>=pos; i--)
//        {
//            m_sequence[i+1] = m_sequence[i];
//        }
//        m_size++;
//        m_sequence[pos] = value;
//
//        return (pos);
//    }
    return (-1);
    
}

int Sequence::insert(const ItemType& value)
{
    int p;
    if (m_size<max_size)
    {
        p = m_size;
        int s=m_size;
        m_size++;
        for (int i=0; i<s; i++)
        {
            if (value <= m_sequence[i])
            {
                p=i;
                break;
            }
        }
        
        for(int j=s-1; j>=p; j--)
        {
            m_sequence[j+1] = m_sequence[j];
        }
        
        m_sequence[p] = value;
        //m_size++;
    }
    else
    {
        p=-1;
    }
    return (p);
}

bool Sequence::erase(int pos)
{
    if (pos<m_size && pos>=0)
    {
        for(int i=pos; i<m_size-1; i++)
        {
            //m_sequence[i-1] = m_sequence[i];
            m_sequence[i] = m_sequence[i+1];
        }
        m_size--;
        //m_sequence[m_size] = "";
        
        return true;
    }
    return false;
}


int Sequence::remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
    int counter=0;
    
    for (int i=0; i<m_size; i++)
    {
        if (m_sequence[i] == value)
        {
            this->erase(i);
            counter++;
            i--;
        }
    }
    
    
    
//    //int i=0;
//    ItemType* ptr = m_sequence;
//
////    while(i < m_size)
////    {
//        while(*(ptr) == value)
//        {
//            ptr++;
//            m_size--;
//            counter++;
//        }
//        //*(m_sequence+i) = *(ptr+i);
//        *m_sequence = *ptr;
//        ptr++;
//        m_sequence++;
//
//        //i++;
//    //}
    return (counter);
}


bool Sequence::get(int pos, ItemType& value) const
{
    if(pos<m_size && pos>=0)
    {
        value = m_sequence[pos];
        return true;
    }
    return false;
}


bool Sequence::set(int pos, const ItemType& value)
{
    if (pos<m_size && pos>=0)
    {
        m_sequence[pos] = value;
        return true;
    }
    return false;
}


int Sequence::find(const ItemType& value) const

{
    int p = -1;
    
    for (int i=0; i<m_size; i++)
    {
        if (m_sequence[i] == value)
        {
            p = i;
            break;
        }
    }
    return (p);
}

void Sequence::swap(Sequence& other)
{
//    //copy other into temp
//    //evokes copy constructor
//    Sequence temp(other);
//
//    //set the size of other into the size of this sequence
//    other.m_size = this->m_size;
//
//    //set the size of this sequence to the size of temp
//    this->m_size = temp.m_size;
//
//
//    //set this to other
//    other.m_sequence = this->m_sequence;
//
//    //set temp to this
//    this->m_sequence = temp.m_sequence;
    
    
    
    
    
    //change size
    int temp=other.size();
    //std::cerr<<"temp= "<<temp<<std::endl;
    other.m_size = this->m_size;
    //std::cerr<<"other.m_size= "<<other.m_size<<std::endl;
    //std::cerr<<"other.size()= "<<other.size()<<std::endl;
    m_size = temp;
    //std::cerr<<"m_size= "<<m_size<<std::endl;
    
    
    temp = other.max_size;
    other.max_size = max_size;
    max_size = temp;
    
    //change pointers of m_sequence and other.m_sequence
    ItemType* t = other.m_sequence;
    other.m_sequence = m_sequence;
    m_sequence = t;
    
    
    
}

