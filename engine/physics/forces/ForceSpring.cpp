#include "./ForceSpring.h"

ForceSpring::ForceSpring():
	m_other(NULL),
	m_springConstant(1.0f),
	m_equilibrium(1.0f){}

ForceSpring::ForceSpring(Object* other, float springConstant, float equilibrium):
	m_other(other),
	m_springConstant(springConstant),
	m_equilibrium(equilibrium){}
	
void ForceSpring::updateForce(Object* obj, float dt){
	glm::vec2 force = obj->getPosition();
	
	force -= m_other->getPosition();

	float magnitude = glm::length(force);
	magnitude = magnitude - m_equilibrium;
	
	magnitude *= m_springConstant;
	
	force = glm::normalize(force);


	force *= -magnitude;
	obj->getRigidbody2D()->addForce(force);
}

void ForceSpring::setEquilibrium(float equilibrium){
	m_equilibrium = equilibrium;
}

void ForceSpring::setSpringConstant(float springConstant){
	m_springConstant = springConstant;
}
	
