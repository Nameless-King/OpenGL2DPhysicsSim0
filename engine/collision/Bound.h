#pragma once

#include <cmath>

#include "../../Dependencies/glm/glm.hpp"
#include "../maths/EngineMath.h"

enum BoundingType{
	NA = 0,
	AxisAligned = 1,
	Circle = 2,
	Oriented = 3
};

class Bound{
public:
	BoundingType m_type;
	glm::vec2* m_halfExtents;
	glm::vec3* m_center;
	glm::vec3* m_scale;

	Bound(); // COMPLETE
	Bound(glm::vec3* center, glm::vec3* scale, const float* pvertices, BoundingType type); // COMPLETE
	Bound(const Bound& bound);
	~Bound(); // COMPLETE
	
	inline BoundingType getBoundingType() const {return m_type;} //COMPLETE
	inline const glm::vec3* getCenter() const {return m_center;} // COMPLETE
	inline const glm::vec2* getHalfExtents() const {return m_halfExtents;} // COMPLETE
	inline const glm::vec3* getScale() const {return m_scale;} // COMPLETE

	void getPositionXY(glm::vec2& pos);

	glm::vec2 getCopyCenterXY() const; // COMPLETE
	glm::vec3 getCopyCenterXYZ() const; // COMPLETE
	glm::vec2 getCopyHalfExtentsXY() const; // COMPLETE
	
	void setHalfExtents(glm::vec2* halfExtents) ; // COMPLETE
};