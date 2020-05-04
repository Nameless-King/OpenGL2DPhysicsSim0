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
    struct ObjectRegistration{
        Object* object;
        ObjectRegistration* next;
    };

    private:
        Shader* m_shader;
        Texture* m_texture;
        ObjectRegistration* m_firstObject;
        Object* m_player;

        CollisionBatchResolver* m_collisionResolver;
        CollisionData m_tempContact;
        unsigned int m_maxContacts;
        ForceGravity m_forceGravity;
        unsigned int m_numCollisions;
        unsigned int m_numObjects;

    public:
        SceneTest();
        SceneTest(Shader* shader, Texture* texture);
        ~SceneTest();

        void render(GWindow* window);
        void update(GWindow* window);
        void renderGUI();
    
    private:
        void input(GWindow* window);
        void addObject(Object* newObject);
        void startFrame();
        void generateContacts();
        void integrate(float dt);
        void runPhysics(float dt);
        void testBoxCollision(Object* obj1, Object* obj2, CollisionData* col);

};