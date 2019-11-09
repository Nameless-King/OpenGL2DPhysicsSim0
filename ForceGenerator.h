#pragma once

#include "./Object.h"

class ForceGenerator{
	public:
		virtual void updateForce(Object* obj,float dt) = 0;
};
