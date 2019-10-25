#ifndef AABB_H_
#define AABB_H_

#include <cmath>
#include <algorithm> //for std::min(a,b)
#include <iostream>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"


struct Collision{
	bool colliding;
	glm::vec2 distance;
	glm::vec2 collisionNormal;
	//glm::vec3 penetrationDepth;
	float penetrationDepth;
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
	
	const glm::vec2 getCenter() const { return glm::vec2(m_center->x,m_center->y);}
	const glm::vec2 getHalfExtents() const {return m_halfExtent;}
	const int getBBType() const {return m_bbType;}
};

#endif
	