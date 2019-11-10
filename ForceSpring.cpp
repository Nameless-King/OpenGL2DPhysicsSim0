#include "./ForceSpring.h"

ForceSpring::ForceSpring(Object* other, float springConstant, float restLength):
	m_other(other),
	m_springConstant(springConstant),
	m_restLength(restLength){}
	
void ForceSpring::updateForce(Object* obj, float dt){
	glm::vec2 force;
	
	obj->getPos(force);
	std::cout << force.x << " " << force.y << std::endl;
	force -= glm::vec2(m_other->getPos().x,m_other->getPos().y);
	
	float magnitude = glm::length(force);
	magnitude = fabs(magnitude - m_restLength);
	magnitude *= m_springConstant;
	
	force = glm::normalize(force);
	force *= -magnitude;
	obj->getRigidBody2D()->addForce(force);
}
	
