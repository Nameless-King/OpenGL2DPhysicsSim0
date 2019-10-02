#pragma once

#include "VertexArrayObj.h"
#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Object{
private:
	VertexArrayObj *m_pvao;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	Object(VertexArrayObj *vao,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Object();
	
	
	VertexArrayObj* getVAO() const {return m_pvao;}
	glm::mat4 getModelMatrix();
	
	
	
};