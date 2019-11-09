#include "./ForceGravity.h"

ForceGravity::ForceGravity(const glm::vec2& gravity):m_gravity(gravity){}

void ForceGravity::updateForce(Object* obj,float dt){
	obj->getRigidBody2D()->addForce(m_gravity*obj->getRigidBody2D()->getMass());
}
