#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

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
#include "./engine/scene/Scene.h"

class SceneOBB : public Scene {
    //Moved to Scene.h
    // struct ObjectRegistration {
    //     Object* object;
    //     ObjectRegistration* next;
    // };

private:
    Shader* m_shader;
    Texture* m_texture;
    Object* m_player;
    Object* m_test;

    unsigned int m_maxContacts;
    ForceGravity m_forceGravity;

public:
    SceneOBB();
    SceneOBB(Shader* shader, Texture* texture);
    ~SceneOBB();

    void render(GWindow* window);
    void update(GWindow* window);
    void renderGUI();

private:
    void input(GWindow* window);
    void generateContacts();
    void runPhysics(float dt);

};