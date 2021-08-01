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


class SceneBoundTest : public Scene{
	private:
		Shader* m_shader;
		Texture* m_texture;
		Object* m_object;


	public:
		SceneBoundTest();
		SceneBoundTest(Shader* shader, Texture* texture);
		~SceneBoundTest();
		
		void render(GWindow* window);
		void update(GWindow* window);
		void renderGUI();
	private:
		void input(GWindow* window);
		void runPhysics(float dt, GWindow* window = NULL);
};
