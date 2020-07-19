#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./engine/Object.h"
#include "./engine/scene/Scene.h"
#include "./engine/graphics/Shader.h"
#include "./engine/graphics/Renderer.h"
#include "./engine/graphics/Texture.h"
#include "./engine/io/GWindow.h"
#include "./engine/io/GInput.h"
#include "./engine/collision/Bound.h"
#include "./engine/collision/CollisionBatchResolver.h"
#include "./engine/collision/Collision.h"
#include "./engine/physics/Physics2D.h"
#include "./engine/physics/forces/ForceGravity.h"

#include "./experimental/QuadTree.h"

class SceneQuadTreeDemo : public Scene {
    private:
        QuadTreeDemo* m_demo;
    public:
        SceneQuadTreeDemo();
        ~SceneQuadTreeDemo();

        void render(GWindow* window);
        void update(GWindow* window);
        void renderGUI();
    private:
        void input(GWindow* window);
        void checkBounds();
        void runPhysics(float dt, GWindow* window = NULL);
};
