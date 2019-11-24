#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"


class RigidBody2D{
	private:
		glm::vec2* m_sigmaForce;
		glm::vec2* m_velocity;
		glm::vec2* m_acceleration;
		float m_damping; //0 to stop, 1 to never, 0.995 ok
		float m_mass;
	
	public:
		RigidBody2D();
		RigidBody2D(float mass);
		~RigidBody2D();

		void addForce(float fx,float fy);
		void addForce(glm::vec2 force);

		void zeroForce();
		
		void setForce(float fx,float fy);
		void setMass(float mass);
		void setDamping(float damping);
		void setAcceleration(float ax, float ay);
		void setVelocity(float vx, float vy);
		void setVelocity(glm::vec2 vel);

		inline float getMass() {return m_mass;}
		inline float getInverseMass() {return 1.0f/m_mass;}
		inline float getDamping() { return m_damping;}

		inline glm::vec2* getVelocity() const {return m_velocity;}
		inline glm::vec2* getAcceleration() const {return m_acceleration;}
		inline glm::vec2* getSigmaForce() const {return m_sigmaForce;}

		void getVelocity(glm::vec2& vel);

		bool hasInfiniteMass();

};
