#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>

#include "./Object.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"
#include "./Hitbox.h"
#include "./CollisionBatchResolver.h"
#include "./ObjectContact.h"
#include "./Physics2D.h"

class ScenePhysicsSystem : public Scene{
 struct ObjectRegistration{
		Object* object;
		ObjectRegistration* next;
	};

	private:
		std::string m_title;
		Shader* m_shader;
		Texture* m_texture;
		ObjectRegistration* m_firstObject;

		//Contacts are added to the resolver immediately after creation.
		/*struct ContactRegistration{
			ObjectContact* contact;
			ContactRegistration* next;
		};*/
		//ContactRegistration* m_firstContact;

		CollisionBatchResolver* m_collisionResolver;

		unsigned int m_maxContacts;
	
	public:
		ScenePhysicsSystem();
		ScenePhysicsSystem(Shader* shader, Texture* texture, const float vertices[]);
		~ScenePhysicsSystem();
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
		/**
		 * Initializes the world for a simulation frame. This clears
		 * the force accumulators for objects in the world. After
		 * claaing this, the objects can have their forces for this
		 * frame added.
		 */
		void startFrame();

		/**
		 * Interates through Object registry and generates all contacts.
		 * Each contact that is generated is then passed to the collision resolver.
		 */
		//unsigned int generateContacts();
		void generateContacts();
	

		/**
		 * Integrates all the objects in this world forward in time
		 * by the given duration
		 */
		void integrate(float dt);

		/**
		 * Processes all the physics for the object world.
		 */
		void runPhysics(float dt);
};
