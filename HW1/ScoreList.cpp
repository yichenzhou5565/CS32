#include "ScoreList.h"

ScoreList::ScoreList() 
{
    
}

bool ScoreList::add(unsigned long score)
{
    if (score<=100 && score>=0 )
    {
        if (m_sequence.insert(score) !=- 1)
        {
            return true;
        }
            //in this way, m_sequnece is listed in an order such that
            //from the lowest score to the highest score
    }
    return false;
}

bool ScoreList::remove(unsigned long score)
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
{
    if (m_sequence.find(score) != -1)
    {
        m_sequence.erase(m_sequence.find(score));
        return true;
    }
    return false;
}

int ScoreList::size() const  // Return the number of scores in the list.
{
    return (m_sequence.size());
}

unsigned long ScoreList::minimum() const
{
    if (m_sequence.size() == 0)
    {
        return NO_SCORE;
    }
    
    ItemType min_score;
    m_sequence.get(0, min_score);
    
    return (min_score);
}

unsigned long ScoreList::maximum() const
{
    if (m_sequence.size() == 0)
    {
        return NO_SCORE;
    }
    
    ItemType max_score;
    m_sequence.get(m_sequence.size()-1, max_score);
    
    return (max_score);
}
