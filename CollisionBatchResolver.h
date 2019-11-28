#pragma once

#include "./ObjectContact.h"

#include <vector>

class CollisionBatchResolver{
    protected:
        //max number of iterations the algorithm is allowed
        unsigned int m_iterations;
        //used to keep track of the max number of algorithms used
        unsigned int m_iterationsUsed;
        //used to store contacts on each update
        std::vector<ObjectContact> m_contacts;
    
    public:
        CollisionBatchResolver(unsigned int iterations);
        ~CollisionBatchResolver();
        inline unsigned int getIterationsUsed() const { return m_iterationsUsed;}

        void resolveContacts(float dt);
        void registerContact(ObjectContact contact);
        void resetRegistry();
};