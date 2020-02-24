#include "./OBB.h"

OBB::OBB():
    m_center(NULL),
    m_rotation(0.0f),
    m_halfExtents(NULL),
    m_localX(glm::vec2(1.0f,0.0f)),
    m_localY(glm::vec2(0.0f,1.0f))
    {}

OBB::~OBB(){
    delete m_halfExtents;
}

glm::vec3 OBB::getCenterXYZCopy(){
    return glm::vec3(m_center->x,m_center->y,m_center->z);
}

glm::vec2 OBB::getCenterXYCopy(){
    return glm::vec2(m_center->x,m_center->y);
}

glm::vec2 OBB::getHalfExtentsXYCopy(){
    return glm::vec2(m_halfExtents->x,m_halfExtents->y);
}

void OBB::setCenter(glm::vec3* center){
    m_center = center;
}

void OBB::setHalfExtents(glm::vec2* halfExtents){
    m_halfExtents = halfExtents;
}