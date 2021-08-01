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

class Object {
public:
	bool m_transformationChanged;

private:
	Bound* m_bound;
	Rigidbody2D* m_rigidbody;
	
	glm::vec2 m_position;
	float m_rotation;
	glm::vec2 m_scale;

	int m_numVertices;
	const float* m_localVertices;
	float* m_globalVertices;

public:
	Object();
	Object(glm::vec2 position, float rotation, glm::vec2 scale);
	Object(const Object& object);
	~Object();


	void rotateDegrees(float degrees);

	void setPosition(float xPos, float yPos);
	void setPosition(glm::vec2 pos);
	void setRotation(float rot);
	void setScale(float xScl, float yScl);

	void addRigidbody2D(float mass);
	void createBound(BoundingType type);

	glm::mat4 getModelMatrix();

	glm::vec2 getPosition();
	inline glm::vec2 getScale() { return m_scale; }
	inline float getRotation() {return m_rotation;}

	inline const float* getVertices() { return m_localVertices; }
	const float* getGlobalVertices();

	int getNumVertices();

	inline Bound* getBound() { return m_bound; }
	inline Rigidbody2D* getRigidbody2D() { return m_rigidbody; }

	void updateGlobalVertices();

};
	