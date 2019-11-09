#pragma once

#include "./RigidBody2D.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class Particle{
	private:
		glm::vec2 m_position;
		RigidBody2D* m_rb;
	
	public:
		Particle();
		Particle(glm::vec2 position);
		~Particle();
		
		/* a possible implementation
		[1 0 dx]
		[0 1 dy] * [x,y,0] = [x+dx,y+dy,0]
		[0 0  1]
		*/
		glm::mat3 getModelMatrix();
		
		void setPos(float xPos, float yPos);
		void addRigidBody2D(RigidBody2D* rb);
		glm::vec2 getPos();
		inline RigidBody2D* getRigidBody2D() const {return m_rb;}
	
};