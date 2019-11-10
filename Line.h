#pragma once

#include "./Particle.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class Line{
	private:
		Particle* m_endpoint1;
		Particle* m_endpoint2;
		
	public:
		Line();
		Line(Particle* endpoint1,Particle* endpoint2);
		~Line();
		
};