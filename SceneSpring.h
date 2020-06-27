#pragma once

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
#include "./engine/physics/forces/ForceGravity.h"
#include "./engine/physics/forces/ForceFakeSpring.h"
#include "./engine/physics/forces/ForceSpring.h"
#include "./engine/physics/forces/ForceBungee.h"
#include "./engine/scene/Scene.h"


class SceneSpring : public Scene{
	private:
		float m_springConstant;
		bool m_useGravity;
		Shader* m_shader;
		Texture* m_texture;
		Object* m_staticObj;
		Object* m_hangingObj;
		ForceGravity m_forceGravity;
		ForceSpring m_forceSpring;
		ForceBungee m_forceBungee;
		ForceFakeSpring m_forceFakeSpring;
		int m_currentType;
		
	public:
		SceneSpring();
		SceneSpring(Shader* shader, Texture* texture);
		~SceneSpring();
		
		void render(GWindow* window);
		void update(GWindow* window);
		void renderGUI();
	private:
		void input(GWindow* window);
		void runPhysics(float dt, GWindow* window = NULL);
};
