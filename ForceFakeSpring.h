#pragma once

#include "./ForceGenerator.h"
#include "./Object.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

class ForceFakeSpring : public ForceGenerator{
    private:
        Object* m_other;
        float m_springConstant;
        float m_damping;
    public:
        ForceFakeSpring();
        ForceFakeSpring(Object* m_other,float springConstant,float damping);
        virtual void updateForce(Object* object, float dt);
        void setSpringConstant(float springConstant);
        void setDamping(float damping);
        inline float getSpringConstant() const {return m_springConstant;}
        inline float getDamping() const {return m_damping;}
};