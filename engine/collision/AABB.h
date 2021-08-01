#pragma once

#include "./Bound.h"

class AABB:public Bound{
public:
	AABB() :Bound() {}
	AABB(const AABB& bound):Bound(bound){}
	AABB(glm::vec2* center, float* rotation, glm::vec2* scale, const float* pvertices, int vertexCount):Bound(center,rotation,scale,pvertices,vertexCount,BoundingType::AxisAligned){}
	
};