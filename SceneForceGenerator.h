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
#include "./ForceGravity.h"
#include "./ForceSpring.h"
#include "./ForceDrag.h"
#include "./ForceBungee.h"
#include "./ForceFakeSpring.h"

class SceneForceGenerator : public Scene{
	private:
		std::string m_title;
		float m_springConstant;
		bool m_useGravity;
		Shader* m_shader;
		Texture* m_texture;
		Object* m_staticObj;
		Object* m_hangingObj;
		ForceGravity m_forceGravity;
		ForceSpring m_forceSpring;
		ForceDrag m_forceDrag;
		ForceBungee m_forceBungee;
		ForceFakeSpring m_forceFakeSpring;
		int m_currentType;
		
	public:
		SceneForceGenerator();
		SceneForceGenerator(Shader* shader, Texture* texture, const float vertices[]);
		~SceneForceGenerator();
		
		std::string getSceneTitle() const;
		void render(Window* window);
		void update(Window* window);
		void renderGUI();
	private:
		void input(Window* window);
};
