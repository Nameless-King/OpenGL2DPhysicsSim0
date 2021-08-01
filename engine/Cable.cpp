#include "./Cable.h"

float Cable::currentLength() const{
    glm::vec2 relativePosition = m_objects[0]->getPosition() - m_objects[1]->getPosition();
    return glm::length(relativePosition);
}

unsigned int Cable::fillContact(CollisionData* contact, unsigned int limit) const{
    float length = currentLength();

    //if not overextended
    if(length < m_maxLength){
        return 0;
    }

    //return contact in passed ObjectContact reference
    glm::vec2 normal = m_objects[1]->getPosition() - m_objects[0]->getPosition();
    normal = glm::normalize(normal);
    contact->m_contactNormal = normal;
    contact->m_restitution = m_restitution;
    contact->m_penetrationDepth = length - m_maxLength;

    return 1;
}