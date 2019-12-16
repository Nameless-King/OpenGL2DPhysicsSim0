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
#include <vector>

#include "./Object.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"
#include "./ForceGravity.h"
#include "./ObjectContact.h"
#include "./Physics2D.h"
#include "./CollisionBatchResolver.h"
#include "./Hitbox.h"

class SceneRestingContact : public Scene{
	private:
		std::string m_title;
		float m_speed;
		Shader* m_shader;
		Texture* m_texture;
		Object* m_player;
		Object* m_restingObject;
		Object* m_wall;
		std::vector<Object*> m_objects;
		ObjectContact m_contactResolver;
		ForceGravity m_forceGravity;
		CollisionBatchResolver m_collisionBatchResolver;
	
	public:
		SceneRestingContact();
		SceneRestingContact(Shader* shader, Texture* texture, const float vertices[]);
		~SceneRestingContact();
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
		void boundCheck(Window* window, Object* object);
		void testBoxCollision(Object* obj1, Object* obj2, ObjectContact* col);
};
