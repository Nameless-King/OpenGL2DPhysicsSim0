#include "./RigidBody2D.h"

RigidBody2D::RigidBody2D():
	m_mass(1.0f),
	m_damping(0.0f){
	m_sigmaForce = new glm::vec2(0.0f,0.0f);
	m_velocity = new glm::vec2(0.0f,0.0f);
	m_acceleration = new glm::vec2(0.0f,0.0f);
}

RigidBody2D::RigidBody2D(float mass):
	m_mass(mass),
	m_damping(0.0f){
	m_sigmaForce = new glm::vec2(0.0f,0.0f);
	m_velocity = new glm::vec2(0.0f,0.0f);
	m_acceleration = new glm::vec2(0.0f,0.0f);
}

RigidBody2D::~RigidBody2D(){
	delete m_sigmaForce;
	delete m_velocity;
	delete m_acceleration;
}

void RigidBody2D::addForce(float fx, float fy){
	m_sigmaForce->x+=fx;
	m_sigmaForce->y+=fy;
}

void RigidBody2D::addForce(glm::vec2 force){
	*(m_sigmaForce)+=force;
}

void RigidBody2D::setForce(float fx,float fy){
	m_sigmaForce->x = fx;
	m_sigmaForce->y = fy;
}

void RigidBody2D::setMass(float mass){
	m_mass = mass;
}

void RigidBody2D::setDamping(float damping){
	m_damping = damping;
}

void RigidBody2D::setAcceleration(float ax, float ay){
	m_acceleration->x = ax;
	m_acceleration->y = ay;
}

void RigidBody2D::setVelocity(float vx, float vy){
	m_velocity->x = vx;
	m_velocity->y = vy;
}