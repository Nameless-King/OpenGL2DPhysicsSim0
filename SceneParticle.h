#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>
#include <vector>

#include "./Particle.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Window.h"

class SceneParticle : public Scene{
	private:
		std::string m_title;
		Shader* m_shader;
		std::vector<Particle*> m_particles;
		bool m_active;
		unsigned int m_renderAmount;
	
	public:
		SceneParticle();
		SceneParticle(Shader* shader);
		~SceneParticle();
		std::string getSceneTitle() const;
		bool isActive() const;
		void render(Window* window);
		void update(Window* window);
		void setActive(bool active);
		void renderGUI();
		
};