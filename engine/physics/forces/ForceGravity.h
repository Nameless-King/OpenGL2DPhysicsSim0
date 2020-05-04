#pragma once 

#include "./ForceGenerator.h"
#include "../../Object.h"
#include "../../../Dependencies/glm/glm.hpp"
#include "../../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../../../Dependencies/glm/gtc/matrix_transform.hpp"

class ForceGravity: public ForceGenerator{
    glm::vec2 m_gravity;

    public:
        ForceGravity(const glm::vec2& gravity);
        virtual void updateForce(Object* obj, float dt);
        void setGravity(float gx, float gy);
        inline glm::vec2 getGravity() { return m_gravity;}
};