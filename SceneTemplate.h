
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"

#include "./engine/Object.h"
#include "./engine/collision/Bound.h"
#include "./engine/collision/Collision.h"
#include "./engine/collision/CollisionBatchResolver.h"
#include "./engine/graphics/Shader.h"
#include "./engine/graphics/Renderer.h"
#include "./engine/graphics/Texture.h"
#include "./engine/io/GWindow.h"
#include "./engine/io/GInput.h"
#include "./engine/physics/Physics2D.h"
#include "./engine/scene/Scene.h"


class SceneTemplate : public Scene{
	private:
		Shader* m_shader;
		Texture* m_texture;
		Object* m_player;
	
	public:
		SceneTemplate();
		SceneTemplate(Shader* shader, Texture* texture);
		~SceneTemplate();
		void render(GWindow* window);
		void update(GWindow* window);
		void renderGUI();
	private:
		void input(GWindow* window);
		void runPhysics(float dt, GWindow* window = NULL);
};
