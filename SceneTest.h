#pragma once



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

#include <GLFW/glfw3.h>


class SceneTest : public Scene{

    private:
        Shader* m_shader;
        Texture* m_texture;
        Object* m_player;

        unsigned int m_maxContacts;
        ForceGravity m_forceGravity;
        float m_playerSpeed;

    public:
        SceneTest();
        SceneTest(Shader* shader, Texture* texture);
        ~SceneTest();

        void render(GWindow* window);
        void update(GWindow* window);
        void renderGUI();
    
    private:
        void input(GWindow* window);
        void runPhysics(float dt);

};