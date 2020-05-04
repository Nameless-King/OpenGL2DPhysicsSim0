#pragma once

#include "./Bound.h"

class OBB : public Bound{
public:
	glm::vec2 m_localX;
	glm::vec2 m_localY;
	float m_rotation;

	OBB():
		m_localX(glm::vec2(1.0f,0.0f)),
		m_localY(glm::vec2(0.0f,1.0f)),
		m_rotation(0)
	{}
	
	OBB(glm::vec3* center, glm::vec3* scale, const float* pvertices):
		m_localX(glm::vec2(1.0f,0.0f)),
		m_localY(glm::vec2(0.0f,1.0f)),
		m_rotation(0.0f),
		Bound(center,scale,pvertices,BoundingType::Oriented)
	{}

	OBB(const OBB& bound):
		m_localX(bound.m_localX),
		m_localY(bound.m_localY),
		m_rotation(bound.m_rotation),
		Bound(bound)
	{}
	
};