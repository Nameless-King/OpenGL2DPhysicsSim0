#pragma once

#include <cmath>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

struct Collision{
	bool colliding;
	glm::vec2 distance;
};

enum BBType{
	NA = 0,
	AxisAligned = 1,
	Circle = 2,
};

class AABB{//or alt class for circle stuff
private:
	BBType m_bbType;
	glm::vec3* m_center;
	glm::vec2 m_halfExtent;
	glm::vec3* m_scale;
public:
	AABB();
	AABB(glm::vec3* center,glm::vec3* scale,const float* vertices, BBType type);
	~AABB();
	
	static Collision getCollision(AABB box1, AABB box2);
	const glm::vec3 getCenter() const { return *m_center;}
	const glm::vec2 getHalfExtents() const {return m_halfExtent;}
	const int getBBType() const {return m_bbType;}
};
	