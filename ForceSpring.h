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
		float m_equilibrium;
	public:
		ForceSpring();
		ForceSpring(Object* other, float springConstant, float m_equilibrium);
		virtual void updateForce(Object* object, float dt);
		void setEquilibrium(float equilibrium);
		void setSpringConstant(float springConstant);
		inline float getEquilibrium() const {return m_equilibrium;}
		inline float getSpringConstant() const{return m_springConstant;}
};