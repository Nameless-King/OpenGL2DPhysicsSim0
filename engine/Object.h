#pragma once

#include <iostream>

#include "./collision/Bound.h"
#include "./collision/AABB.h"
#include "./collision/OBB.h"
#include "./collision/Circle.h"
#include "./maths/EngineMath.h"
#include "./physics/Rigidbody2D.h"
#include "./graphics/Renderer.h"

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

class Object{
public:
	bool m_transformationChanged;
private:
	Bound* m_bound;
	Rigidbody2D* m_rigidbody;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	const float* m_localVertices;
	float* m_globalVertices;
public:
	Object();
	Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Object(const Object& object);
	~Object();
	
	glm::mat4 getModelMatrix();
	
	void rotateDegrees(float degrees);

	void setPos(float xPos, float yPos, float zPos);
	void setPos(float xPos, float yPos);
	void setPos(glm::vec2 pos);
	void setRot(float xRot, float yRot, float zRot);
	void setScl(float xScl, float yScl, float zScl);
	
	void addRigidbody2D(Rigidbody2D* rb);
	void createBound(BoundingType type);
	
	
	inline glm::vec3 getPositionXYZ() {return m_position;}
	inline glm::vec3 getRotationXYZ() {return m_rotation;}
	inline glm::vec3 getScaleXYZ() {return m_scale;}
	inline const float* getVertices() {return m_localVertices;}
	const float* getGlobalVertices();
	
	glm::vec2 getPositionXY();
	glm::vec2 getRotationXY();
	glm::vec2 getScaleXY();
	
	inline Bound* getBound(){ return m_bound;}
	inline Rigidbody2D* getRigidbody2D() {return m_rigidbody;}
	
};
	