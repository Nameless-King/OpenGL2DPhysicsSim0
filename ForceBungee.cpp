#include "./ForceBungee.h"

ForceBungee::ForceBungee():  m_other(NULL),m_springConstant(1.0f),m_equilibrium(1.0f){}

ForceBungee::ForceBungee(Object* other, float springConstant, float equilibrium):
    m_other(other),
    m_springConstant(springConstant),
    m_equilibrium(equilibrium){}

void ForceBungee::updateForce(Object* object, float dt){
    glm::vec2 force;
    object->getPos(force);
    force -= m_other->getPos2();

    float magnitude = glm::length(force);
    if(magnitude <= m_equilibrium) return;

    magnitude = m_springConstant * (m_equilibrium - magnitude);

    glm::normalize(force);
    force *= -magnitude;
    object->getRigidBody2D()->addForce(force);
}

void ForceBungee::setSpringConstant(float springConstant){
    m_springConstant = springConstant;
}

void ForceBungee::setEquilibrium(float equilibrium){
    m_equilibrium = equilibrium;
}

