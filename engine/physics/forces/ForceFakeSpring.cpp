#include "./ForceFakeSpring.h"

ForceFakeSpring::ForceFakeSpring():
    m_other(NULL),
    m_springConstant(0),
    m_damping(0)
{}

ForceFakeSpring::ForceFakeSpring(Object* other, float springConstant, float damping):
    m_other(other),
    m_springConstant(springConstant),
    m_damping(damping)
{}

void ForceFakeSpring::updateForce(Object* object, float dt){
    //should check if object has infinite mass
    if(object->getRigidbody2D()->hasInfiniteMass()){
        return;
    }
    //get relative position of object to other
    glm::vec2 position = object->getPosition();
    position -= m_other->getPosition();

    //calc constants and check if in bounds
    float gamma = 0.5f * sqrt(4*m_springConstant-m_damping*m_damping);
    if(gamma == 0.0f){
        return;
    }
    glm::vec2 c = position * (m_damping/(2.0f*gamma)) + *(object->getRigidbody2D()->getVelocity()) * (1.0f / gamma);

    //calc target position
    glm::vec2 target = position * cosf(gamma*dt) + c * sinf(gamma * dt);
    target *= expf(-0.5f * dt * m_damping);

    //calc resulting acceleration and therefore the force
    glm::vec2 accel = (target - position) * (1.0f/dt * dt) - *(object->getRigidbody2D()->getVelocity()) * dt;
    object->getRigidbody2D()->addForce(accel * object->getRigidbody2D()->getMass());
}

void ForceFakeSpring::setSpringConstant(float springConstant){
    m_springConstant = springConstant;
}

void ForceFakeSpring::setDamping(float damping){
    m_damping = damping;
}