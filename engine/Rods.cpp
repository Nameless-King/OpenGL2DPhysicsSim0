#include "./Rods.h"

float Rods::currentLength() const{
    glm::vec2 relativePosition = m_objects[0]->getPosition() - m_objects[1]->getPosition();
    return glm::length(relativePosition);
}

unsigned int Rods::fillContact(CollisionData* contact, unsigned int limit) const{
    float currentLen = currentLength();

    //if not overextending
    if(currentLen == m_length){
        return 0;
    }

    contact->object[0] = m_objects[0];
    contact->object[1] = m_objects[1];

    glm::vec2 normal = m_objects[1]->getPosition() - m_objects[0]->getPosition();
    normal = glm::normalize(normal);

    //value of contact normal depends on whether this is extending or compressing
    if(currentLen > m_length){
        contact->m_contactNormal = normal;
        contact->m_penetrationDepth = currentLen - m_length;
    }else{
        contact->m_contactNormal = -normal;
        contact->m_penetrationDepth = m_length - currentLen
    }

    //always use 0 (no bounciness)
    contact->m_restitution = 0;

    return 1;
}