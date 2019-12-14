#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Object.h"
#include "./AABB.h"


class ObjectContact{
    public:
        Object* object[2];
        float m_restitution;
        glm::vec2 m_contactNormal;
        Collision m_collision;
        float m_penetrationDepth;
    public:
        ObjectContact();
        ObjectContact(const ObjectContact& contact);
        //deals with contact resolution for both velocity and interpenetration
        void resolve(float dt, Collision col);
        void resolve(float dt);
        void resolveRestingContact(float dt, Collision col);
        //calculate closing velocity
        float calculateClosingVelocity() const;
    private:
        //calculates impulse
        void resolveVelocity(float dt);
        void resolveRestingContactVelocity(float dt);
        void resolveInterpenetration(float dt, Collision col);
        void resolveInterpenetration(float dt);
};