#include "./ForceRegistry.h"

void ForceRegistry::updateForces(float dt){
    Registry::iterator i = m_registration.begin();
    for(;i!=m_registration.end();i++){
        i->fg->updateForce(i->obj,dt);
    }
}