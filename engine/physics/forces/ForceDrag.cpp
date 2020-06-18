#include "./ForceDrag.h"

ForceDrag::ForceDrag():m_k1(1.0f),m_k2(1.0f){}

ForceDrag::ForceDrag(float k1,float k2):m_k1(k1),m_k2(k2){}

void ForceDrag::updateForce(Object* obj, float dt){
	RigidBody2D* objRB = obj->getRigidbody2D();
	glm::vec2 force;
	objRB->getVelocity(force);

	float dragCoeff = glm::length(force); 
	dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff;
	
	glm::normalize(force);
	force *= -dragCoeff;
	objRB->addForce(force);
	
}

void ForceDrag::setK1(float k1){
	m_k1 = k1;
}

void ForceDrag::setK2(float k2){
	m_k2 = k2;
}
