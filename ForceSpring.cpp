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
	glm::vec2 force;
	
	obj->getPos(force);
	
	force -= glm::vec2(m_other->getPos().x,m_other->getPos().y);
	
	float magnitude = glm::length(force);
	magnitude = fabs(magnitude - m_equilibrium);
	magnitude *= m_springConstant;
	
	
	glm::normalize(force);
	

	force *= -magnitude;
	obj->getRigidBody2D()->addForce(force);
}

void ForceSpring::setEquilibrium(float equilibrium){
	m_equilibrium = equilibrium;
}

void ForceSpring::setSpringConstant(float springConstant){
	m_springConstant = springConstant;
}
	
