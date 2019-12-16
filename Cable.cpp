#include "./Cable.h"

float Cable::currentLength() const{
    glm::vec2 relativePosition = m_objects[0]->getPos2() - m_objects[1]->getPos2();
    return glm::length(relativePosition);
}

unsigned int Cable::fillContact(ObjectContact* contact, unsigned int limit) const{
    float length = currentLength();

    //if not overextended
    if(length < m_maxLength){
        return 0;
    }

    //return contact in passed ObjectContact reference
    glm::vec2 normal = m_objects[1]->getPos2() - m_objects[0]->getPos2();
    normal = glm::normalize(normal);
    contact->m_contactNormal = normal;
    contact->m_restitution = m_restitution;
    contact->m_penetrationDepth = length - m_maxLength;

    return 1;
}