#pragma once

#include "./Collision.h"

#include <vector>

class CollisionBatchResolver{
    protected:
        //max number of iterations the algorithm is allowed
        unsigned int m_iterations;
        //used to keep track of the max number of algorithms used
        unsigned int m_iterationsUsed;
        //used to store collisions on each update
        std::vector<CollisionData> m_collisions;
    
    public:
        CollisionBatchResolver(unsigned int iterations);
        ~CollisionBatchResolver();
        inline unsigned int getIterationsUsed() const { return m_iterationsUsed;}

        unsigned int numOfCollisions();

        void resolveContacts(float dt);
        void registerContact(CollisionData collision);
        void resetRegistry();
};