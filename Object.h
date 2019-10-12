#pragma once

#include "VertexArrayObj.h"
#include "AABB.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Object{
private:
	const float* m_vertices;
	AABB m_bb;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	Object();
	Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Object();
	
	
	
	glm::mat4 getModelMatrix();
	void setPos(float xPos, float yPos, float zPos);
	void setRot(float xRot, float yRot, float zRot);
	void setScl(float xScl, float yScl, float zScl);
	void addVertices(const float vertices[]);
	void createAABB(BBType type);
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScl();
	inline AABB getBoundingBox() const {return m_bb;}
	
	
	
};