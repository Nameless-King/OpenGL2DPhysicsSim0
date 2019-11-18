#include "./ObjectContact.h"

void ObjectContact::resolve(float dt,Collision col){
    resolveVelocity(dt);
    resolveInterpenetration(dt, col);
}

float ObjectContact::calculateClosingVelocity() const{
    glm::vec2 relativeVelocity = *(object[0]->getRigidBody2D()->getVelocity());
    if(object[1]){
        relativeVelocity -= *(object[1]->getRigidBody2D()->getVelocity());
    }
    return glm::dot(relativeVelocity,m_contactNormal);
}

void ObjectContact::resolveVelocity(float dt){
    //find velocity in direction of collision
    float closingVelocity = calculateClosingVelocity();

    //check whether needs to be resolved
    if(closingVelocity >0){
        //then no impulse required
        return;
    }

    //calc new closing velocity
    float newClosingVelcity = -closingVelocity * m_restitution;

    float deltaVelocity = newClosingVelcity - closingVelocity;

    //apply change in proportion to inverse mass
    float totalInverseMass = object[0]->getRigidBody2D()->getInverseMass();
    if(object[1]){
        totalInverseMass += object[1]->getRigidBody2D()->getInverseMass();
    }

    if(totalInverseMass<=0){
        return;
    }

    //calc impulse
    float impulse = deltaVelocity / totalInverseMass;

    //find impulse per unit of inverse mass
    glm::vec2 impulsePerMass = m_contactNormal * impulse;

    //apply impulse in direction of contact
    //proportional to inverse mass
    object[0]->getRigidBody2D()->setVelocity(*(object[0]->getRigidBody2D()->getVelocity()) + impulsePerMass * object[0]->getRigidBody2D()->getInverseMass());
    if(object[1]){
        //object[1] goes in opposite direction
        object[1] -> getRigidBody2D()->setVelocity(*(object[1]->getRigidBody2D()->getVelocity()) + impulsePerMass * -object[1]->getRigidBody2D()->getInverseMass());
    }
}

void ObjectContact::resolveInterpenetration(float dt,Collision col){
    //if no penetration
    if(col.penetrationDepth <= 0){
        return;
    }

    float totalInverseMass = object[0]->getRigidBody2D()->getInverseMass();
    if(object[1]){
        totalInverseMass += object[1]->getRigidBody2D()->getInverseMass();
    }

    //both have infinite mass
    if(totalInverseMass <= 0){
        return;
    }

    glm::vec2 movePerMass = col.collisionNormal * (-col.penetrationDepth/totalInverseMass);

    float percent = 0.1f;

    object[0]->setPos(object[0]->getPos2() + percent * -movePerMass * object[0]->getRigidBody2D()->getInverseMass());
    if(object[1]){
        object[1]->setPos(object[1]->getPos2() + percent * movePerMass*object[1]->getRigidBody2D()->getInverseMass());
    }
}