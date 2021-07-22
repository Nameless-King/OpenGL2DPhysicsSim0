#pragma once

#include "../../Dependencies/glm/glm.hpp"
#include "./GPhysicsFlags.h"


class Rigidbody2D{
	private:
		glm::vec2* m_sigmaForce;
		glm::vec2* m_velocity;
		glm::vec2* m_acceleration;
		glm::vec2* m_accelerationLastFrame;
		float m_damping; //0 to stop, 1 to never, 0.995 ok
		float m_mass;

		//angular components
		float* m_rotation; // angle
		float m_angularVelocity;
		float m_torque;

		GPF_Type GPF_Rigidbody;
	
	public:
		Rigidbody2D();
		Rigidbody2D(const Rigidbody2D& rb);
		Rigidbody2D(float* rotation, float mass);
		~Rigidbody2D();

		void addForce(float fx,float fy);
		void addForce(glm::vec2 force);

		void addGPF(GPF_Type flag);
		void removeGPF(GPF_Type flag);
		bool checkGPF(GPF_Type flag);

		void zeroForce();
		
		void setForce(float fx,float fy);
		void setMass(float mass);
		void setDamping(float damping);
		void setAngularVelocity(float vel);
		void setTorque(float tor);
		void setAcceleration(float ax, float ay);
		void setAccelerationLastFrame(float ax, float ay);
		void setVelocity(float vx, float vy);
		void setVelocity(glm::vec2 vel);

		inline float getMass() {return m_mass;}
		inline float getInverseMass() {return 1.0f/m_mass;}
		inline float getDamping() { return m_damping;}
		inline float getRotation() {return *m_rotation;}
		inline float getAngularVelocity() {return m_angularVelocity;}
		inline float getTorque() {return m_torque;}

		inline glm::vec2* getVelocity()  {return m_velocity;}
		inline glm::vec2* getAcceleration()  {return m_acceleration;}
		inline glm::vec2* getAccelerationLastFrame() {return m_accelerationLastFrame;}
		inline glm::vec2* getSigmaForce()  {return m_sigmaForce;}

		void getVelocity(glm::vec2& vel);

		bool hasInfiniteMass();

};
