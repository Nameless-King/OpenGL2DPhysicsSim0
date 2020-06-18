#pragma once

#include "../../../Dependencies/glm/glm.hpp"
#include "../../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../../../Dependencies/glm/gtc/matrix_transform.hpp"

#include "./ForceGenerator.h"
#include "../../Object.h"

class ForceDrag : public ForceGenerator{
	float m_k1;
	float m_k2;

	public:
		ForceDrag();
		ForceDrag(float k1, float k2);
		virtual void updateForce(Object* obj, float dt);
		void setK1(float k1);
		void setK2(float k2);
		inline float getK1() const{return m_k1;}
		inline float getK2() const{return m_k2;}
};
