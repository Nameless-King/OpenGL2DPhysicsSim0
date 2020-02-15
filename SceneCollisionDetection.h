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
#include "./ForceGravity.h"
#include "./Experimental.h"

class SceneCollisionDetection : public Scene{

	struct ObjectRegistration{
		Object* object;
		ObjectRegistration* next;
	};

	private:
		std::string m_title;
		Shader* m_shader;
		Texture* m_texture;
		ObjectRegistration* m_firstObject;
		Object* m_player;

		CollisionBatchResolver* m_collisionResolver;
		ObjectContact m_tempContact;
		unsigned int m_maxContacts;
		ForceGravity m_forceGravity;
		unsigned int m_numCollisions;
		unsigned int m_numObjects;
	
	public:
		SceneCollisionDetection();
		SceneCollisionDetection(Shader* shader, Texture* texture, const float vertices[]);
		~SceneCollisionDetection();
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
		void addObject(Object* newObject);
		void startFrame();
		void generateContacts();
		void integrate(float dt);
		void runPhysics(float dt);
		void testBoxCollision(Object* obj1, Object* obj2, ObjectContact* col);
};
