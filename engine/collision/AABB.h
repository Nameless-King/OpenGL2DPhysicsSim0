#pragma once

#include "./Bound.h"

class AABB:public Bound{
public:
	AABB();
	AABB(const AABB& bound):Bound(bound){}
	AABB(glm::vec3* center, glm::vec3* scale, const float* pvertices):Bound(center,scale,pvertices,BoundingType::AxisAligned){}
	
};