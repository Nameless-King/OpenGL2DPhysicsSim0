#include "./RigidBody2D.h"

RigidBody2D::RigidBody2D():
	m_mass(1.0f),
	m_damping(0.0f),
	m_sigmaForce(new glm::vec2(0.0f,0.0f)),
	m_velocity(new glm::vec2(0.0f,0.0f)),
	m_acceleration(new glm::vec2(0.0f,0.0f))
{}

RigidBody2D::RigidBody2D(float mass):
	m_mass(mass),
	m_damping(0.0f),
	m_sigmaForce(new glm::vec2(0.0f,0.0f)),
	m_velocity(new glm::vec2(0.0f,0.0f)),
	m_acceleration(new glm::vec2(0.0f,0.0f))
{}

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

void RigidBody2D::zeroForce(){
	m_sigmaForce->x = 0.0f;
	m_sigmaForce->y = 0.0f;
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

void RigidBody2D::setVelocity(glm::vec2 vel){
	m_velocity->x = vel.x;
	m_velocity->y = vel.y;
}

void RigidBody2D::getVelocity(glm::vec2& vel){
	vel = *m_velocity;
}

bool RigidBody2D::hasInfiniteMass(){
	return m_mass < 0;
}