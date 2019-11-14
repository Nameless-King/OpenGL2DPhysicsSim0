#include "./ForceBuoyancy.h"

ForceBuoyancy::ForceBuoyancy():
    m_maxDepth(0),
    m_volume(0),
    m_waterHeight(0),
    m_liquidDensity(0){}

ForceBuoyancy::ForceBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity){}

ForceBuoyancy::updateForce(Object* object, float dt){

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