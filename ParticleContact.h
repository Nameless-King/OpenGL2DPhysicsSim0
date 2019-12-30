#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Particle.h"

class ParticleContact{
    public:
        Particle* particle[2];
    public:
        void resolve(float dt);
};