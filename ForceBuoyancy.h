#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./ForceGenerator.h"
#include "./Object.h"

class ForceBuoyancy : public ForceGenerator {
    private:
        float m_maxDepth;
        float m_volume;
        //height of water above y = 0
        float m_waterHeight;
        float m_liquidDensity;

    public:
        ForceBuoyancy();
        ForceBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity);

        virtual void updateForce(Object* object, float dt);

        inline float getMaxDepth() const {return m_maxDepth;}
        inline float getVolume() const {return m_volume;}
        inline float getWaterHeight() const {return m_waterHeight;}
        inline float getLiquidDensity() const {return m_liquidDensity;}

        void setMaxDepth(float maxDepth);
        void setVolume(float volume);
        void setWaterHeight(float waterHeight);
        void setLiquidDensity(float liquidDensity);

};