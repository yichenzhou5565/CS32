#include "Sequence.h"

Sequence::Sequence()
: m_size(0),head(nullptr), tail(nullptr)
{
    
}

Sequence::Sequence(const Sequence& other) //copy constructor
{
    m_size = other.m_size;
    
    //if other is an empty sequence
    if (other.m_size == 0)
    {
        head = tail = nullptr;
    }
    
    else
    {
        //set head
        head = new Node;
        head->data = other.head->data;
        head->prev = nullptr;
        
        Node* p;
        p = head;
        Node* q = other.head->next;
        
        //copy rest of the sequence
        while (q != nullptr)
        {
            Node* k = new Node;
            k->data = q->data;
            p->next = k;
            k->prev = p;
            q = q->next;
            p = k;
        }
    }
}


//assignment operator
Sequence& Sequence::operator=(const Sequence& rhs)
{
    //if we are not assigning rhs to itself
    if (&rhs != this)
    {
        Sequence temp = rhs;
        swap(temp);
        
        return *this;
    }
    
    return *this;
}

//destructor of the class sequence
Sequence::~Sequence()
{
    Node* p = head;
    while(p != nullptr)
    {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

void Sequence::dump() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cerr<<p->data<<" ";
        p=p->next;
    }
    std::cerr<<std::endl;
}



bool Sequence::empty() const
{
    //check by size
    if (m_size == 0)
    {
        return true;
    }
    return false;
}


int Sequence::size() const
{
    return (m_size);
}



int Sequence::insert(int pos, const ItemType& value)
{
    //if pos is not desirable
        //return -1
    if (pos>m_size || pos<0)
    {
        pos = -1;
    }
    
    else
    {
        //if inserting in the very front or inserting the first element
            //then we need not update tail
        if (pos==0 || head == nullptr)
        {
            Node* p;
            p = new Node;
            p->data = value;
            p->next = head;
            p->prev = nullptr;
            head = p;
            //m_size++;
        }
        
        //if inserting at the end
            //then we need not update head
        else if (pos == m_size )
        {
            Node* p=head;
            while (p->next != nullptr)
            {
                p=p->next;
            }
            
            Node* latest = new Node;
            latest->data = value;
            
            latest->prev=p;
            p->next=latest;
            latest->next=nullptr;
        }
        
        
        //if inserting in the middle
        else
        {
            Node* p = head;
            //now we want p to point JUST above pos
            int counter=0;
            while (p->next != nullptr)
            {
                if (counter == pos-1)
                {
                    break;
                }
                counter++;
                p = p->next;
            }
            
            Node* latest = new Node;
            //set the data of latest into value
            latest->data = value;
            
            //we need to update
            // 1) next of p
            latest->next = p->next;
            p->next = latest;
            
            // 2) prev of original node right after p
            latest->prev = (p->next)->prev;
            (p->next)->prev = latest;
            //m_size++;
        }
        m_size++;
    }
    return pos;
}


int Sequence::insert(const ItemType& value)
{
    int pos=0;
    
    Node* p = head;
    
    //if there are no elements yet, hendle it in a different way
    // to avoid tracing nullptr and breaking thread
    if (head == nullptr)
    {
        insert(0, value);
        return 0;
    }
    
    
    //now we want p to point at JUST one position before insertion
    while (p->next != nullptr)
    {
        if (value <= (p->data))
        {
            break;
        }
        pos++;
        p = p->next;
    }

    if (p->data < value)
    {
        pos++;
    }
    else
    {
        p=p->prev;
    }

    //use the previously written insert function
    insert(pos, value);


//    //now we are in the same situation as the previous "insert" member funtion
//
//    if (pos == 0 || head == nullptr)
//    {
//        Node* p;
//        p = new Node;
//        p->data = value;
//        p->next = head;
//        p->prev = nullptr;
//        head = p;
//    }
//
//    else if (pos == m_size)
//    {
//        Node* p=head;
//        while (p->next != nullptr)
//        {
//            p=p->next;
//        }
//
//        //std::cerr<<"**"<<p->data<<"** ";
//
//        Node* latest = new Node;
//        latest->data = value;
//
//        latest->prev = p;
//        latest->next = nullptr;
//        p->next=latest;
//        tail = latest;
//
//        //std::cerr<<"**"<<p->data<<"** ";
//    }
//
//    else
//    {
//        Node* latest = new Node;
//        latest->data = value;
//
//        latest->next = p->next;
//
//        latest->prev = p;
//
//        p->next->prev = p;
//        p->next = latest;
//
//    }
//    m_size++;
    
    return (pos);
}



bool Sequence::erase(int pos)
{
    if (pos>=0 && pos<m_size)
    {
        
        //if it is already an empty sequence
        if (head == nullptr)
            return false;
        
        //if insert in the first position
        if(pos == 0)
        {
            
            //if there are more than one element in the sequence
            if (m_size != 1)
            {
                
                
                Node* p = head;
                p=p->next;
                p->prev = nullptr;
                delete head;
                head = p;
            }
            
            else
            {
//                head->next = nullptr;
//                head->prev = nullptr;
                delete head;
                head = nullptr;
                //tail = nullptr;
            }
        }
        
        //if we want to erase the last element
//        else if (pos == m_size-1)
//        {
//            Node* p = tail;
//
//            p=p->prev;
//            p->next = nullptr;
//
//            delete tail;
//            tail = p;
//        }
        
        //if we want ot erase the element in the middle
        else
        {
            //std::cerr<<"uuuuuu"<<std::endl;
            int counter=0;
            Node* p = head;
            
            while (p != nullptr)
            {
                if (counter == pos-1 && p->next!=nullptr)
                {
                    break;
                }
                counter++;
                p=p->next;
            } //now p is pointing JUST above the thing we want to delete
            
            
            //p=p->prev;
            
            if(p!= nullptr)
            {
                Node* killMe = p->next;
                Node* after=killMe->next;
                
                if (killMe != nullptr)
                {
                    p->next = killMe->next;
                
                    if (after != nullptr)
                    {
    //                    p->next = killMe->next;

                        after->prev = killMe->prev;
                    }
                
//                else
//                {
//                    head = nullptr;
//                }
                
                //Node* after=killMe->next;
                
                    delete killMe;}
            }
        }
        m_size--; //update the size accordingly
        return true;
    }
    
    return false;
    
}


int Sequence::remove(const ItemType& value)
{
    int i=0; //this is the counter
    while (this->find(value) != -1) //when the value is present in the sequence
    {
        int pos = this->find(value);
        this->erase(pos);
        i++;
    }
    return (i);
    
    
    
    
    
    
//    int counter = 0;
//    int pos=0;
//    Node* p = head;
//
//    while (p != nullptr)
//    {
//        if (p->data == value)
//        {
//            if (head == nullptr)
//            {
//                break;
//            }
//
//            counter++;
//            this->erase(pos);
//            pos--;
//
//        }
//
//        pos++;
//
//        //if (p->next != nullptr)
//        p=p->next;
//
////        p = p->next;
//
//
//
//    }
//    return (counter);
}


bool Sequence::get(int pos, ItemType& value) const
{
    int counter=0;
    Node* p = head;
    
    //if pos is valid
    if (pos>=0 && pos<m_size)
    {
        //we want p pointing at pos th entry in the sequence
        while (p != nullptr)
        {
            if (counter == pos)
            {
                break;
            }
            
            counter++;
            p=p->next;
            
        }
        //copy the value in the p now into the parameter
        value = p->data;
        return true;
    }
    return false;
}


bool Sequence::set(int pos, const ItemType& value)
{
    int counter = 0;
    Node* p = head;
    
    //if pos is valid
    if (pos>=0 && pos<m_size)
    {
        //we want p pointing at pos th entry in our sequence
        while (p != nullptr)
        {
            if (counter == pos)
            {
                break;
            }
            counter++;
            p=p->next;
        }
        
        //now set the value
        p->data = value;
        
        return true;
    }
    return false;
}


int Sequence::find(const ItemType& value) const
{
    int pos=-1;
    int counter=0;
    Node* p = head;
    
    while (p != nullptr)
    {
        //if found, break
        if (p->data == value)
        {
            pos = counter;
            break;
        }
        counter++;
        p = p->next;
    }
    
    return (pos);
}



void Sequence::swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
    //swap the sizes
    int temp;
    temp = other.m_size;
    other.m_size = m_size;
    m_size = temp;
    
    //swap the head pointers
    Node* h=other.head;
    other.head = head;
    head = h;
    
    //swap the tail pointers
    Node* t = other.tail;
    other.tail = tail;
    tail = t;
    
}


//if seq2 is a subsequence of seq 1, return the smallest position
//otherwise, return -1
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    //int pos=0;
    //int counter=0;
    
    //check from size and emptiness
    if (seq1.size() < seq2.size() || seq1.size()==0 || seq2.size()==0)
    {
        return -1;
    }
    
    for (int i=0; i<seq1.size(); i++)
    {
        int j=0;
        for ( j=0; j<seq2.size(); j++)
        {
            ItemType x, y;
            seq1.get(i+j, x);
            seq2.get(j, y);
            if (x != y)
            {
                break;
            }
        }
        
        if (j == seq2.size())
        {
            return i;
        }
    }
    return (-1);
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence result1;
    
    if (seq1.size() >= seq2.size())
    {
        ItemType x;
        //then we try to insert elements of 2 into 1
        
        //first copy all elements of 1 into result
        for (int k=seq1.size()-1; k>=0; k--)
        {
            ItemType temp;
            seq1.get(k, temp);
            result1.insert(0, temp);
        }
        
        
        for (int i=0; i<seq2.size(); i++)
        {
            seq2.get(i, x);
            int j=2*i+1;
            result1.insert(j, x);
        }
        
    }
    
    
    //if seq2 is longer
    else
    {
        //std::cerr<<"** ";
        ItemType x;
        //then we try to insert elements of 1 into 2

        //first copy all elements of 2 into result
        for (int k=seq2.size()-1; k>=0; k--)
        {
            ItemType temp;
            seq2.get(k, temp);
            result1.insert(0, temp);

        }

        for (int i=0; i<seq1.size(); i++)
        {
            seq1.get(i, x);
            int j=2*i;
            result1.insert(j, x);
        }

    }
    
    result1.swap(result); //set result 1 into result
    
}
