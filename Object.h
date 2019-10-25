#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>

#include "./VertexArrayObj.h"
#include "./AABB.h"

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
	float m_accel;
	glm::vec2 m_velocity; 
	float m_restitution;
	float m_mass;
public:
	Object();
	Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Object();
	
	
	
	glm::mat4 getModelMatrix();
	
	void setVelocity(float xVel,float yVel);
	void setPos(float xPos, float yPos, float zPos);
	void setRot(float xRot, float yRot, float zRot);
	void setScl(float xScl, float yScl, float zScl);
	
	void setAcceleration(float accel);
	void setRestitution(float restitution);
	void setMass(float mass);
	
	void addVertices(const float vertices[]);
	
	void createAABB(BBType type);
	
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScl();
	
	inline AABB getBoundingBox() const {return m_bb;}
	
	inline float getAcceleration() const {return m_accel;}
	inline float getMass() const {return m_mass;}
	inline float getRestitution() const {return m_restitution;}
	
	inline glm::vec2 getVelocity() {return m_velocity;}
	
	
	
};

#endif