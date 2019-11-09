#pragma once

#include "./Object.h"
#include "./ForceGenerator.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class ForceDrag : public ForceGenerator{
	float m_k1;
	float m_k2;

	public:
		ForceDrag(float k1, float k2);
		virtual void updateForce(Object* obj, float dt);
};
