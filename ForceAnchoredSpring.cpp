#include "./ForceAnchoredSpring.h"

ForceAnchoredSpring::ForceAnchoredSpring(float px, float py,float springConstant, float equilibrium):
    m_springConstant(springConstant),
    m_equilibrium(equilibrium){
    m_anchor = new glm::vec2(px,py);
    }

ForceAnchoredSpring::~ForceAnchoredSpring(){
    delete m_anchor;
}

void ForceAnchoredSpring::updateForce(Object* object, float dt){
    glm::vec2 force = object->getPositionXY();
    force -= * m_anchor;

    float magnitude = glm::length(force);
    magnitude = fabs(magnitude - m_equilibrium);
    magnitude *= m_springConstant;

    glm::normalize(force);
    force *= -magnitude;
    object->getRigidBody2D()->addForce(force);
}

void ForceAnchoredSpring::setAnchor(float px, float py){
    m_anchor->x = px;
    m_anchor->y = py;
}

void ForceAnchoredSpring::setSpringConstant(float k){
    m_springConstant = k;
}

void ForceAnchoredSpring::setEquilibrium(float equilibrium){
    m_equilibrium = equilibrium;
}