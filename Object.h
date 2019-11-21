#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>

#include "./VertexArrayObj.h"
#include "./AABB.h"
#include "./RigidBody2D.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Object{
private:
	const float* m_vertices;
	AABB m_bb;
	RigidBody2D* m_rb;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	Object();
	Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Object();
	
	glm::mat4 getModelMatrix();

	void setPos(float xPos, float yPos, float zPos);
	void setPos(float xPos, float yPos);
	void setPos(glm::vec2 pos);
	void setRot(float xRot, float yRot, float zRot);
	void setScl(float xScl, float yScl, float zScl);
	
	void addRigidBody2D(RigidBody2D* rb);
	void addVertices(const float vertices[]);
	void createAABB(BBType type);
	
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScl();
	
	inline AABB getBoundingBox() const {return m_bb;}
	inline RigidBody2D* getRigidBody2D() const {return m_rb;}
	inline glm::vec2 getPos2() const {return glm::vec2(m_position.x,m_position.y);}

	void getPos(glm::vec2& pos);
	
};

#endif