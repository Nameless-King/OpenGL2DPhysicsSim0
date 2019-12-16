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

#include "./Object.h"
#include "./Physics2D.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"
#include "./Hitbox.h"

class SceneForces : public Scene{
	private:
		std::string m_title;
		float m_force;
		bool m_useGravity;
		Shader* m_shader;
		Texture* m_texture;
		Object* m_player;
		
	public:
		SceneForces();
		SceneForces(Shader* shader, Texture*, const float vertices[]);
		~SceneForces();
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
};
