#include "./Object.h"



Object::Object():
	m_position(glm::vec3(0.0f,0.0f,0.0f)),
	m_rotation(glm::vec3(0.0f,0.0f,0.0f)),
	m_scale(glm::vec3(1.0f,1.0f,1.0f)),
	m_vertices(nullptr),
	m_bb(AABB()),
	m_rb(NULL),
	m_accel(0),
	m_restitution(0),
	m_mass(0),
	m_velocity(glm::vec2(0.0f,0.0f)){
	}

Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_vertices(nullptr),
	m_bb(AABB()),
	m_rb(NULL),
	m_accel(0),
	m_restitution(0),
	m_mass(0),
	m_velocity(glm::vec2(0.0f,0.0f)){
	}
	
Object::~Object(){
	delete m_rb;
}

glm::mat4 Object::getModelMatrix(){
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,m_position);
	model = glm::rotate(model,glm::radians(m_rotation.x),glm::vec3(1.0f,0.0f,0.0f));
	model = glm::rotate(model,glm::radians(m_rotation.y),glm::vec3(0.0f,1.0f,0.0f));
	model = glm::rotate(model,glm::radians(m_rotation.z),glm::vec3(0.0f,0.0f,1.0f));
	model = glm::scale(model,m_scale);
	return model;
}

//depricated
void Object::setVelocity(float xVel, float yVel){
	m_velocity = glm::vec2(xVel,yVel);
}

void Object::setPos(float xPos, float yPos, float zPos){
	m_position = glm::vec3(xPos,yPos,zPos);
}

void Object::setPos(float xPos, float yPos){
	m_position = glm::vec3(xPos,yPos,m_position.z);
}

void Object::setRot(float xRot, float yRot, float zRot){
	m_rotation = glm::vec3(xRot, yRot, zRot);
}

void Object::setScl(float xScl, float yScl, float zScl){
	m_scale = glm::vec3(xScl,yScl,zScl);
}

//depricated
void Object::setAcceleration(float accel){
	m_accel = accel;
}

//depricated
void Object::setRestitution(float restitution){
	m_restitution = restitution;
}

//depricated
void Object::setMass(float mass){
	m_mass = mass;
}

void Object::addRigidBody2D(RigidBody2D* rb){
	m_rb = rb;
}

void Object::addVertices(const float vertices[]){
	m_vertices = vertices;
}

void Object::createAABB(BBType type){
	m_bb = AABB(&m_position,&m_scale,m_vertices,type);
}

glm::vec3 Object::getPos(){
	return m_position;
}

glm::vec3 Object::getRot(){
	return m_rotation;
}

glm::vec3 Object::getScl(){
	return m_scale;
}

void Object::getPos(glm::vec2& pos){
	pos = glm::vec2(m_position.x,m_position.y);
}

