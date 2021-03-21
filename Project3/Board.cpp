#include "Board.h"
#include <list>

Board::Board(int nHoles, int nInitialBeansPerHole)
: m_nHoles(nHoles)
{
    //if the number of holes is not positive, act as if it were 1
    if (m_nHoles < 1)
        m_nHoles = 1;
    //if the number of beans is negative, act as if it were 0
    if (nInitialBeansPerHole<0)
        nInitialBeansPerHole=0;
    
    std::list<int>::iterator itr; //iterator
    
    north.push_back(0); //push 0 as the beans in pot
    south.push_back(0);
    
    for (int i=0; i<m_nHoles; i++) //push the initial beans into the pot
    {
        north.push_back(nInitialBeansPerHole);
        south.push_back(nInitialBeansPerHole);
    }
    
    
}


int Board::holes() const //return the number of holes in each side
{
    return m_nHoles;
}


int Board::beans(Side s, int hole) const
{
    std::list<int>::const_iterator itr; //iterator
    
    if (hole<0 || hole>m_nHoles) //if invalid
        return (-1);
    
    if (s==NORTH) ///if side is north  ////iterate the north list
    {
        itr = north.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;
        }
    }
    else ///if side is south...iterate the south list
    {
        itr = south.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;
        }
    }
    return (*itr); //return num of beans in that hole
}


int Board::beansInPlay(Side s) const
{
    int result=0;
    std::list<int>::const_iterator itr;
    
    if (s==NORTH) //if we want to focus on north side...
    {
        itr = north.begin(); //iterate from the beginning of north ...
        itr++;
        while (itr != north.end()) //iteraet through the entire list...
        {
            result += *(itr); //and count total # of beans
            itr++;
        }
        
    }
    
    else
    {
        itr = south.begin();//if we want to focus on north side...
        itr++;
        while (itr != south.end()) //iteraet through the entire list...
        {
            result += *(itr); //count total...
            itr++;
        }
    }
    return result; //return total in that list's holes
}


int Board::totalBeans() const //total # is the sum of 2 pots and 2 sides' inplays'
{
    return (*north.begin() + *south.begin() + beansInPlay(NORTH) + beansInPlay(SOUTH));
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if (hole<1 || hole>m_nHoles) //if argument invalid
    {
        return false;
    }
    
    std::list<int>::iterator itr;
    if (s==SOUTH) //if south
    {
        
        itr = south.begin();
        //let iterator point right to the hole
        for (int i=0; i!=hole; i++)
        {
            itr++;
        }
        
        int num = *(itr); //how many beans are there in the hole
        
        if (num == 0) //if there is no beans in the pot, return false
        {
            return false;
        }
        
        *(itr) = 0; //set the target hole into 0
        endHole = hole;
        
        itr++; //now iterator pointing to the thing next to hole
        
        while (num > 0)
        {
            while (itr != south.end() && num>0) //iterate through the south and throw beans
            {
                endSide = SOUTH;
                endHole++;
                *(itr) += 1;
                itr++;
                num--;
            }
            
            if (num>0) //if still beans remained, throw 1 into south's pot
            {
                itr = south.begin();
                endHole = 0;
                *(itr) += 1;
                num--;
            }
            
            if (num>0) //if still beans remained, iterate from the last of north
            {
                itr=north.end();
                endSide = NORTH;
                endHole = m_nHoles+1;
                
                itr--;
                while (num>0 && itr!=north.begin())
                {
                    *(itr) += 1; //and throw beans in it
                    endHole--;
                    itr--;
                    num--;
                }
            }
            
            if (num>0) //if still beans remained...iterate agiain from the beginning hole of south
            {
                itr = south.begin();
                itr++;
                endHole = 0;
            }
            
        }
    }
    
    else //if north
    {
        itr = north.begin();
        for (int i=0; i<hole; i++)
        {
            itr++;
        }
        int num = *(itr);
        *(itr) = 0; //iterate to the target hole
        if (num == 0) //if empty
        {
            return false;
        }
        itr--; //move 1 index along the road
        endHole = hole;
        
        while (num > 0)
        {
            while (itr != north.begin()&&num>0) //iterate the north
            {
                endSide = NORTH;
                endHole --;
                *(itr) += 1;
                itr--;
                num--;
            }
            if (num>0) //add one to north pot if beans remained
            {
                endHole = 0;
                itr = north.begin();
                *(itr) += 1;
                num--;
            }
            if (num>0) //if still beans remained, begin from the begnning of south holes
            {
//                itr--;
//                *(itr) += 1;
                itr = south.begin();
                itr++;
                endHole = 0;
                while (itr != south.end() && num>0)
                {
                    endSide = SOUTH;
                    endHole++;
                    *(itr) += 1;
                    itr++;
                    num--;
                }
                //endHole++;
            }
            if (num>0)
            {
                itr = north.end();  //set iterator to the end of north's list
                //endHole++;
                itr--;
                endHole++;
            }
            
        }
    }
    return true;
}


bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    
    if (hole<1 || hole>m_nHoles)
        return false;
    
    std::list<int>::iterator itr;
    
    int numBeans=0;
    
    if (s==SOUTH)
    {
        itr = south.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;
        }
        numBeans = *(itr); //get the beans # in that pot
    }
    if (s==NORTH)
    {
        //itr = iteration(north, hole);
        itr = north.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;
        }
        numBeans = *(itr);  //get the beans # in that pot
    }
    
    *(itr) = 0; //remove everything in that pot
    
    if (potOwner == SOUTH) //let iterator point to the right pot
    {
        itr = south.begin();
    }
    else
    {
        itr = north.begin();
    }
    *(itr) += numBeans; //and move that to the pot
    
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole<0 || hole>m_nHoles || beans<0) //if invalid...
        return false;
    
    std::list<int>::iterator itr;
    if (s==SOUTH)
    {
        //itr=iteration(south, hole);
        itr = south.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;  //iterate to the target...  for south
        }
    }
    else
    {
        itr = north.begin();
        for (int i=0; i!=hole; i++)
        {
            itr++;//iterate to the target...for north
        }
    }
    
    (*(itr)) = beans; //set the beans
    
    
    return true;
}
