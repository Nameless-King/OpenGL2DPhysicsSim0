#pragma once

#include "../../Dependencies/glm/glm.hpp"


class Rigidbody2D{
	private:
		glm::vec2* m_sigmaForce;
		glm::vec2* m_velocity;
		glm::vec2* m_acceleration;
		float m_damping; //0 to stop, 1 to never, 0.995 ok
		float m_mass;

		//angular components
		float m_orientation; // radians
		float m_angularVelocity;
		float m_torque;
	
	public:
		Rigidbody2D();
		Rigidbody2D(const Rigidbody2D& rb);
		Rigidbody2D(float mass);
		~Rigidbody2D();

		void addForce(float fx,float fy);
		void addForce(glm::vec2 force);

		void zeroForce();
		
		void setForce(float fx,float fy);
		void setMass(float mass);
		void setDamping(float damping);
		void setOrientation(float rot);
		void setAngularVelocity(float vel);
		void setTorque(float tor);
		void setAcceleration(float ax, float ay);
		void setVelocity(float vx, float vy);
		void setVelocity(glm::vec2 vel);

		inline float getMass() {return m_mass;}
		inline float getInverseMass() {return 1.0f/m_mass;}
		inline float getDamping() { return m_damping;}
		inline float getOrientation() {return m_orientation;}
		inline float getAngularVelocity() {return m_angularVelocity;}
		inline float getTorque() {return m_torque;}

		inline glm::vec2* getVelocity()  {return m_velocity;}
		inline glm::vec2* getAcceleration()  {return m_acceleration;}
		inline glm::vec2* getSigmaForce()  {return m_sigmaForce;}

		void getVelocity(glm::vec2& vel);

		bool hasInfiniteMass();

};
