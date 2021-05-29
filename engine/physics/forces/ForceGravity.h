#pragma once 

#include "./ForceGenerator.h"
#include "../../Object.h"
#include "../../../Dependencies/glm/glm.hpp"
#include "../../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../../../Dependencies/glm/gtc/matrix_transform.hpp"

enum class GravityType{
    Point,
    Direction
};

class ForceGravity: public ForceGenerator{
    glm::vec2 m_gravity;
    GravityType m_type;
    glm::vec2 m_point;
    float m_magnitude;

    public:
        ForceGravity();
        ForceGravity(const glm::vec2& gravity);
        virtual void updateForce(Object* obj, float dt);
        void setGravity(float gx, float gy);
        void setGravity(const glm::vec2 &gravity);
        inline glm::vec2 getGravity() { return m_gravity;}
        inline void setGravityType(GravityType type) {m_type = type;}
        void setPoint(glm::vec2  point, float mag);
};