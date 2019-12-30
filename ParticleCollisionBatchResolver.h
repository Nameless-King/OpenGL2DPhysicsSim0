#pragma once

#include "./ParticleContact.h"

class ParticleCollisionBatchResolver{
    public:
        unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};