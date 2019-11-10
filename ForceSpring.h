#pragma once

#include "./ForceGenerator.h"
#include "./Object.h"
#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include <iostream>

class ForceSpring : public ForceGenerator{
	private:
		Object* m_other;
		float m_springConstant;
		float m_restLength;
	public:
		ForceSpring(Object* other, float springConstant, float restLength);
		virtual void updateForce(Object* object, float dt);
};