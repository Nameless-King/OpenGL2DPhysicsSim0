#pragma once

#include "./Bound.h"

class AABB:public Bound{
public:
	AABB() :Bound() {}
	AABB(const AABB& bound):Bound(bound){}
	AABB(glm::vec3* center, float* rotation, glm::vec3* scale, const float* pvertices):Bound(center,rotation,scale,pvertices,BoundingType::AxisAligned){}
	
};