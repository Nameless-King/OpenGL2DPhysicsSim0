#include "./CollisionBatchResolver.h"

CollisionBatchResolver::CollisionBatchResolver(unsigned int iterations): 
    m_iterations(iterations),
    m_iterationsUsed(0),
    m_contacts(std::vector<ObjectContact>())
{}

CollisionBatchResolver::~CollisionBatchResolver(){}

void CollisionBatchResolver::resolveContacts(float dt){
    m_iterationsUsed = 0;
    if(!m_contacts.empty()){
        //this is a comment
        m_iterations = m_contacts.size();
        while(m_iterationsUsed < m_iterations){
            //find the contact with the largest closing velocity
            float max = 0;

            unsigned int maxIndex = m_contacts.size()-1;
            for(unsigned int i = 0;i < m_contacts.size();i++){
                
                float closingVelocity = m_contacts[i].calculateClosingVelocity();

                //if(closingVelocity < max){
                if(abs(closingVelocity) > abs(max)){
                    
                    max = closingVelocity;
                    maxIndex = i;
                }
            }

                //resolve contact of largest closing velocity
                m_contacts[maxIndex].resolve(dt);

                m_iterationsUsed++;
            
        
        }
    }
}

void CollisionBatchResolver::registerContact(ObjectContact contact){
    m_contacts.push_back(ObjectContact(contact));
}

void CollisionBatchResolver::resetRegistry(){
    m_contacts.clear();
}

unsigned int CollisionBatchResolver::numOfCollisions(){
    return m_contacts.size();
}