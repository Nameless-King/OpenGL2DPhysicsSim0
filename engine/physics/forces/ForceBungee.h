#pragma once

#include "./ForceGenerator.h"
#include "../../Object.h"

class ForceBungee : public ForceGenerator {
    private:
        Object* m_other;
        float m_springConstant;
        float m_equilibrium;

    public:
        ForceBungee();
        ForceBungee(Object* other, float springConstant, float equilibrium);
        virtual void updateForce(Object* object, float dt);
        inline float getSpringConstant() const {return m_springConstant;}
        inline float getEquilibrium() const {return m_equilibrium;}
        void setSpringConstant(float springConstant);
        void setEquilibrium(float equilibrium);

};