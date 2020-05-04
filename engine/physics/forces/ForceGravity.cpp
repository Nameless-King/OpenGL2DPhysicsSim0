#include "./ForceGravity.h"

ForceGravity::ForceGravity(const glm::vec2& gravity):m_gravity(gravity){}

void ForceGravity::updateForce(Object* obj,float dt){
	if(obj->getRigidbody2D()->hasInfiniteMass()){
		return;
	}

	obj->getRigidbody2D()->addForce(m_gravity*obj->getRigidbody2D()->getMass());
}

void ForceGravity::setGravity(float gx, float gy){
	m_gravity.x = gx;
	m_gravity.y = gy;
}