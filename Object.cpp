#include "Object.h"

Object::Object():
	m_position(glm::vec3(0.0f,0.0f,0.0f)),
	m_rotation(glm::vec3(0.0f,0.0f,0.0f)),
	m_scale(glm::vec3(1.0f,1.0f,1.0f)),
	m_vertices(nullptr),
	m_bb(AABB()){
	}

Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_vertices(nullptr),
	m_bb(AABB()){
	}
	
Object::~Object(){}

glm::mat4 Object::getModelMatrix(){
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,m_position);
	return model;
}


void Object::setPos(float xPos, float yPos, float zPos){
	m_position = glm::vec3(xPos,yPos,zPos);
}

void Object::setRot(float xRot, float yRot, float zRot){
	m_rotation = glm::vec3(xRot, yRot, zRot);
}

void Object::setScl(float xScl, float yScl, float zScl){
	m_scale = glm::vec3(xScl,yScl,zScl);
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

