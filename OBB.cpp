#include "./OBB.h"

OBB::OBB():
    m_center(NULL),
    m_orientation(NULL),
    m_halfExtents(NULL){

}

OBB::~OBB(){
    delete m_orientation;
    delete m_halfExtents;
}

glm::vec3 OBB::getCenterXYZCopy(){
    return glm::vec3(m_center->x,m_center->y,m_center->z);
}

glm::vec2 OBB::getHalfExtentsXYCopy(){
    return glm::vec2(m_halfExtents->x,m_halfExtents->y);
}