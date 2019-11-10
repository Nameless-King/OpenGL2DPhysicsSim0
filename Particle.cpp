#include "./Particle.h"

Particle::Particle():m_position(glm::vec2(0.0f,0.0f)),m_rb(NULL){}

Particle::Particle(glm::vec2 position):m_position(position),m_rb(NULL){}

Particle::~Particle(){
	delete m_rb;
}

glm::mat4 Particle::getModelMatrix(){
	//glm::mat3 model(1.0f);
	
	//float *pMatrix = (float*)glm::value_ptr(model);
	//*(pMatrix+2) = m_position.x;
	//*(pMatrix+5) = m_position.y;
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,glm::vec3(m_position.x,m_position.y,0.0f));
	
	return model;
}

void Particle::setPos(float xPos,float yPos){
	m_position.x = xPos;
	m_position.y = yPos;
}

void Particle::addRigidBody2D(RigidBody2D* rb){
	m_rb = rb;
}

glm::vec2 Particle::getPos(){
	return m_position;
}