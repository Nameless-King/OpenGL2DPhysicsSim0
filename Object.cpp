#include "./Object.h"
Object::Object():
	m_position(glm::vec3(0.0f,0.0f,0.0f)),
	m_rotation(glm::vec3(0.0f,0.0f,0.0f)),
	m_scale(glm::vec3(1.0f,1.0f,1.0f)),
	m_vertices(nullptr),
	m_bb(AABB()),
	m_rb(NULL){
	}

Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_vertices(nullptr),
	m_bb(AABB()),
	m_rb(NULL){
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

void Object::setPos(float xPos, float yPos, float zPos){
	m_position = glm::vec3(xPos,yPos,zPos);
}

void Object::setPos(float xPos, float yPos){
	m_position = glm::vec3(xPos,yPos,m_position.z);
}

void Object::setPos(glm::vec2 pos){
	m_position.x = pos.x;
	m_position.y = pos.y;
}

void Object::setRot(float xRot, float yRot, float zRot){
	m_rotation = glm::vec3(xRot, yRot, zRot);
}

void Object::setScl(float xScl, float yScl, float zScl){
	m_scale = glm::vec3(xScl,yScl,zScl);
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

