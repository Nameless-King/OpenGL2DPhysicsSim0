#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>

#include "./Particle.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Window.h"
#include "./Hitbox.h"
#include "./ParticleContact.h"
#include "./ParticleCollisionBatchResolver.h"

class SceneMassAggregate : public Scene{
	//particle linked list
	struct ParticleRegistration{
		Particle* particle;
		ParticleRegistration* next;
	};

	private:
		std::string m_title;
		ParticleRegistration* m_firstParticle;
		//force generators
		//contact resolver for particles

		struct ContactGeneratorRegistration{
			ParticleCollisionBatchResolver* generator;
			ContactGeneratorRegistration* next;
		};

		ContactGeneratorRegistration* m_firstContactGenerator;

		ParticleContact* m_contacts;

		unsigned int m_maxContacts;



	public:
	/**
	 * Creates a new particle simulator that can handle up to the 
	 * given number of contacts per frame. User can also optionally
	 *  give a number of contact-resultion iterations to use. If the
	 *  number of iterations is not given, then twice the number of
	 * contacts will be used.
	 */
		SceneMassAggregate();
		SceneMassAggregate(unsigned int maxContacts, unsigned int iterations=0);
		~SceneMassAggregate();
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
		/**
		 * Initializes the world for a simulation frame. This clears
		 * the force accumulators for particles in the world. After
		 * calling this, the particles can have their forces for this
		 * frame added.
		 */
		void startFrame();
		/**
		 * Calls each of the registered contact generators to report
		 * their contacts. Returns the number of generated contacts.
		 */
		unsigned int generateContacts();
		/**
		 * Integrates all the particles in this world forward in time
		 * by the given duration
		 */
		void integrate(float dt);
		/**
		 * Processes all the physics for the particle world.
		 */
		void runPhysics(float dt);
};
