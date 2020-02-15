#pragma once

#include <cmath>
#include <algorithm> //for std::min(a,b)
#include <iostream>
#include <assert.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

enum HitboxType{
	NA = 0,
	AxisAligned = 1,
	Circle = 2,
};

class Hitbox{
public:
	glm::vec2 m_halfExtent;
private:
	HitboxType m_hitboxType;
	glm::vec3* m_center;
	glm::vec3* m_scale;
public:
	Hitbox();
	Hitbox(glm::vec3* center,glm::vec3* scale,const float* vertices, HitboxType type);
	~Hitbox();

	const glm::vec2 getCenter() const { return glm::vec2(m_center->x,m_center->y);}
	const glm::vec2 getHalfExtents() const {return m_halfExtent;}
	const int getHitboxType() const {return m_hitboxType;}
	
	//void setHalfExtents(float dx, float dy);
};


	