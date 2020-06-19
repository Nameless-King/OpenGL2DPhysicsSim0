#include "./CollisionOptimizer.h"

CollisionOptimizer::CollisionOptimizer():
    m_front(new Domain()),
    m_postEnd(m_front),
    m_totalGroups(0),
    m_totalObjects(0)
{
    
}

void CollisionOptimizer::createCollisionGroup(const std::string& groupID){
    if(!m_postEnd->valueList){
        m_postEnd->groupID = groupID;
        m_postEnd->valueList = new std::vector<Object*>();
        m_postEnd->next = new Domain();
        m_postEnd = m_postEnd->next;
        m_totalGroups++;
    }
}

void CollisionOptimizer::addObjectToGroup(const std::string& groupID, Object* object){
    while(m_current!=m_postEnd && !groupID.compareTo(m_current->groupID) == 0){
        m_current = m_current->next;
    }

    if(groupID.comparTo(m_current->groupID) == 0){
        m_current->valueList->push_back(object);
        m_totalObjects++;
    }else{
        std::cout << "ERROR: Group " << groupID << " not found!" << std::endl;
    }
}

