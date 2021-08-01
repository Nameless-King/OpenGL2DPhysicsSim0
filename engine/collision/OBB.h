#pragma once

#include "./Bound.h"

class OBB : public Bound{
public:

	OBB():
		Bound()
	{}
	
	OBB(glm::vec2* center, float* rotation, glm::vec2* scale, const float* pvertices,int vertexCount):
		Bound(center,rotation,scale,pvertices,vertexCount,BoundingType::Oriented)
	{}

	OBB(const OBB& bound):
		Bound(bound)
	{}

	OBB(const Bound& bound):
		Bound(bound)
	{}
	
};