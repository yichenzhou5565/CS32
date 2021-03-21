#include "Sequence.h"



Sequence::Sequence() : m_size(0)
{
    
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
    if (pos<=m_size && pos>=0 && m_size<DEFAULT_MAX_ITEMS)
    {
        for (int i=m_size-1; i>=pos; i--)
        {
            m_sequence[i+1] = m_sequence[i];
        }
        m_size++;
        m_sequence[pos] = value;
        
        return (pos);
    }
    return (-1);
    
}

int Sequence::insert(const ItemType& value)
{
    int p;
    if (m_size<DEFAULT_MAX_ITEMS)
    {
        p = m_size;
        for (int i=0; i<m_size; i++)
        {
            if (value <= m_sequence[i])
            {
                p=i;
                break;
            }
        }
        
        for(int j=m_size-1; j>=p; j--)
        {
            m_sequence[j+1] = m_sequence[j];
        }
        
        m_sequence[p] = value;
        m_size++;
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
//    int counter=0;
//    int i=0;
//    ItemType* ptr = m_sequence;
//
//    while(i < m_size)
//    {
//        if(*(ptr+i) == value)
//        {
//            ptr++;
//            m_size--;
//            counter++;
//        }
//        *(m_sequence+i) = *(ptr+i);
//        i++;
//    }
//    return (counter);
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
    return counter;
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
// Exchange the contents of this sequence with the other one.
{
    int min_size;
    
    //if size of this sequence is bigger
    if(other.size()<m_size)
    {
        min_size = other.size();
        for (int i=0; i<min_size; i++)
        {
            ItemType temp;
            
            //set temp to other[i]
            //set other[i] to m_sequence[i]
            //set m_sequence[i] to temp
            other.get(i, temp);
            other.set(i, m_sequence[i]);
            this->set(i, temp);
        }
        
        //insert rest of the elements of m_sequence into other
        
//        for (int j=min_size; j<m_size; j++)
//        {
//            other.insert(j, m_sequence[j]);
//        }

        for (int j=m_size-1; j>=min_size; j--)
        {
            other.insert(min_size, m_sequence[m_size-1]);
            this->erase(m_size-1);
        }
        
        //erase the redundant element of this sequence
        
        
    }
    
    
    
    
    
    
    
    //if size of other is bigger
    else
    {
        min_size = m_size;
        for (int i=0; i<min_size; i++)
        {
            ItemType temp;

            //set temp to other[i]
            //set other[i] to m_sequence[i]
            //set m_sequence[i] to temp
            other.get(i, temp);
            other.set(i, m_sequence[i]);
            this->set(i, temp);
        }

        
        //insert rest of the elements of other into this sequence
        for(int j=other.size()-1; j>=min_size; j--)
        {
            
            ItemType temp;
            other.get(other.size()-1, temp);
            //std::cerr<<temp;
            this-> insert(min_size, temp);
            other.erase(other.size()-1);
        }
        
        
//
//
//
//
//
//        for (int j=min_size; j<other.size(); j++)
//        {
//            ItemType temp;
//            other.set(j, temp);
//            this->insert(j, temp);
//        }

        //erase the redundant element of other

    }
    
    
    
    
    
}
