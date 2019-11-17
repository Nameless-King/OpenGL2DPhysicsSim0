#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Object.h"

class ObjectContact{
    public:
        Object* object[2];
        float m_restitution;
        glm::vec2 m_contactNormal;
    public:
        //deals with contact resolution for both velocity and interpenetration
        void resolve(float dt);
    protected:
        //calculates closing velocity
        float calculateClosingVelocity() const;
    private:
        //calculates impulse
        void resolveVelocity(float dt);
};