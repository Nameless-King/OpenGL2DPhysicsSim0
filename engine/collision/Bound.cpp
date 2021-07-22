#include "./Bound.h"

Bound::Bound():
	m_type(BoundingType::NA),
	m_halfExtents(NULL),
	m_center(NULL),
	m_scale(NULL),
	m_rotation(nullptr),
	m_localX(glm::vec2(1.0f,0.0f)),
	m_localY(glm::vec2(0.0f,1.0f)),
	m_furthestDistance(-1)
{}

Bound::Bound(glm::vec3* center, float* rotation, glm::vec3* scale, const float* pvertices, BoundingType type):
	m_type(type),
	m_center(center),
	m_scale(scale),
	m_halfExtents(EngineMath::calcHalfExtents(pvertices,scale)),
	m_rotation(rotation),
	m_localX(glm::vec2(1.0f,0.0f)),
	m_localY(glm::vec2(0.0f,1.0f)),
	m_furthestDistance(glm::length(*(m_halfExtents)))
{}

Bound::Bound(const Bound& bound):
	m_type(bound.m_type),
	m_halfExtents(new glm::vec2(*bound.m_halfExtents)),
	m_center(bound.m_center),
	m_scale(bound.m_scale),
	m_rotation(bound.m_rotation),
	m_localX(glm::vec2(bound.m_localX)),
	m_localY(glm::vec2(bound.m_localY)),
	m_furthestDistance(bound.m_furthestDistance)
{}

Bound::~Bound(){
	delete m_halfExtents;
}

glm::vec2 Bound::getCopyCenterXY() const {
	return glm::vec2(
		m_center->x,
		m_center->y
	);
}

glm::vec3 Bound::getCopyCenterXYZ() const {
	return glm::vec3(
		m_center->x,
		m_center->y,
		m_center->z
	);
}

glm::vec2 Bound::getCopyHalfExtentsXY() const {
	return glm::vec2(
		m_halfExtents->x,
		m_halfExtents->y
	);
}

void Bound::setHalfExtents(glm::vec2* halfExtents)  {
	delete m_halfExtents;
	m_halfExtents = halfExtents;
}

