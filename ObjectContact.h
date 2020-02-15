#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Object.h"
#include "./Hitbox.h"

class ObjectContact{
    public:
        Object* object[2];
        float m_restitution;
        glm::vec2 m_contactNormal;
        float m_penetrationDepth;
        glm::vec2 m_distance;
        bool m_colliding;
    public:
        ObjectContact();
        ObjectContact(const ObjectContact& contact);
        //deals with contact resolution for both velocity and interpenetration
        void resolve(float dt);
        void resolveRestingContact(float dt);
        //calculate closing velocity
        float calculateClosingVelocity() const;
        static ObjectContact detectContact(Hitbox box1, Hitbox box2);
        static bool isColliding(Hitbox box1, Hitbox box2);
        static bool hasInfiniteMass(Object* argObj);
    private:
        //calculates impulse
        void resolveVelocity(float dt);
        void resolveRestingContactVelocity(float dt);
        void resolveInterpenetration(float dt);
        static glm::vec2 calcContactNormal(ObjectContact);
        static float getSmallestComponent(glm::vec2 vector);
        
        bool correctObjects();
        
};