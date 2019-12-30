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

		struct ContactGeneratorRegistration{
			CollisionBatchResolver* generator;
			ContactGeneratorRegistration* next;
		};

		ContactGeneratorRegistration* m_firstContactGenerator;

		ObjectContact* m_contacts;

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
};
