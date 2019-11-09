#include "./ForceDrag.h"

ForceDrag::ForceDrag(float k1,float k2):m_k1(k1),m_k2(k2){}

void ForceDrag::updateForce(Object* obj, float dt){
	RigidBody2D* objRB = obj->getRigidBody2D();
	glm::vec2 force;
	objRB->getVelocity(force);

	float dragCoeff = glm::length(force); 
	dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff;
	
	glm::normalize(force);
	force *= -dragCoeff;
	objRB->addForce(force);
}
