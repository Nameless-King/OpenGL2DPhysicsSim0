#pragma once

#include "./Bound.h"

class OBB : public Bound{
public:

	OBB():
		Bound()
	{}
	
	OBB(glm::vec3* center, glm::vec3* scale, const float* pvertices):
		Bound(center,scale,pvertices,BoundingType::Oriented)
	{}

	OBB(const OBB& bound):
		Bound(bound)
	{}

	OBB(const Bound& bound):
		Bound(bound)
	{}
	
};