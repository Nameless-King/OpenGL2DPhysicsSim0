#include "./ForceRegistry.h"

void ForceRegistry::updateForces(float dt){
	Registry::iterator i = m_registrations.begin();
	for(;i!=m_registrations.end();i++){
		i->fg->updateForce(i->obj,dt);
	}
}

