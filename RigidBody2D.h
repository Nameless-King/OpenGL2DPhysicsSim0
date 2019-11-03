#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"


class RigidBody2D{
	private:
		glm::vec2* m_velocity;
		glm::vec2* m_acceleration;
		float m_damping; //0 to stop, 1 to never, 0.995 ok
		float m_mass;
	
	public:
		RigidBody2D();
		RigidBody2D(float mass);
		~RigidBody2D();
		void setMass(float mass);
		void setAcceleration(float ax, float ay);
		void setVelocity(float vx, float vy);
		inline float getMass() {return m_mass;}
		inline float getInverseMass() {return 1.0f/m_mass;}
		inline glm::vec2* getVelocity() const {return m_velocity;}
		inline glm::vec2* getAcceleration() const {return m_acceleration;}

};
