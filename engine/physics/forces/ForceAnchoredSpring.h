#pragma once

#include "../../../Dependencies/glm/glm.hpp"
#include "../../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../../../Dependencies/glm/gtc/matrix_transform.hpp"

#include "../../Object.h"
#include "./ForceGenerator.h"

class ForceAnchoredSpring : public ForceGenerator {
    glm::vec2* m_anchor;
    float m_springConstant;
    float m_equilibrium;

    public:
        ForceAnchoredSpring(float px, float py ,float springConstant,float equilibrium);
        ~ForceAnchoredSpring();
        virtual void updateForce(Object* obj, float dt);
        void setAnchor(float px, float py);
        void setSpringConstant(float k);
        void setEquilibrium(float equilibrium);
        inline float getSpringConstant() const {return m_springConstant;}
        inline float getEquilibrium() const {return m_equilibrium;}
        inline glm::vec2* getAnchor() const {return m_anchor;}

};