#include "Object.h"

Object::Object(VertexArrayObj *vao, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
	m_pvao(vao),m_position(position),m_rotation(rotation),m_scale(scale){
	}
	
Object::~Object(){}

glm::mat4 Object::getModelMatrix(){
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,m_position);
	return model;
}