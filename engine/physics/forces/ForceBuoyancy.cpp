#include "./ForceBuoyancy.h"

ForceBuoyancy::ForceBuoyancy():
    m_maxDepth(0),
    m_volume(0),
    m_waterHeight(0),
    m_liquidDensity(0){}

ForceBuoyancy::ForceBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity):
    m_maxDepth(maxDepth),
    m_volume(volume),
    m_waterHeight(waterHeight),
    m_liquidDensity(liquidDensity){}

void ForceBuoyancy::updateForce(Object* object, float dt){
    //calc the submersion depth
    float depth = object->getPosition().y;

    //check if object is out of water
    if(depth >= m_waterHeight + m_maxDepth){
        return;
    }

    glm::vec3 force(0.0f,0.0f,0.0f);

    //check if object is at maximum depth
    if(depth <= m_waterHeight - m_maxDepth){
        force.y = m_liquidDensity * m_volume;
        object->getRigidbody2D()->addForce(force);
        return;
    }

    //otherwise object is partly submerged
    force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2.0f * m_maxDepth;
    object->getRigidbody2D()->addForce(force);
    return;


}

void ForceBuoyancy::setMaxDepth(float maxDepth){
    m_maxDepth = maxDepth;
}

void ForceBuoyancy::setVolume(float volume){
    m_volume = volume;
}

void ForceBuoyancy::setWaterHeight(float waterHeight){
    m_waterHeight = waterHeight;
}

void ForceBuoyancy::setLiquidDensity(float liquidDensity){
    m_liquidDensity = liquidDensity;
}