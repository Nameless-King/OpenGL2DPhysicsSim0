#include "./Bound.h"

Bound::Bound():
	m_type(BoundingType::NA),
	m_halfExtents(NULL),
	m_center(NULL),
	m_scale(NULL)
{}

Bound::Bound(glm::vec3* center, glm::vec3* scale, const float* pvertices, BoundingType type):
	m_type(type),
	m_center(center),
	m_scale(scale),
	m_halfExtents(EngineMath::calcHalfExtents(pvertices,scale))
{}

Bound::Bound(const Bound& bound):
	m_type(bound.m_type),
	m_halfExtents(new glm::vec2(*bound.m_halfExtents)),
	m_center(new glm::vec3(*bound.m_center)),
	m_scale(new glm::vec3(*bound.m_scale))
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

				

	
