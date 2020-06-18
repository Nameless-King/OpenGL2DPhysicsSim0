#include "./CollisionBatchResolver.h"

CollisionBatchResolver::CollisionBatchResolver(unsigned int iterations): 
    m_iterations(iterations),
    m_iterationsUsed(0),
    m_collisions(std::vector<CollisionData>())
{}

CollisionBatchResolver::~CollisionBatchResolver(){}

void CollisionBatchResolver::resolveContacts(float dt){
    m_iterationsUsed = 0;
    if(!m_collisions.empty()){
        m_iterations = m_collisions.size();
        while(m_iterationsUsed < m_iterations){
            //find the collision with the largest closing velocity
            float max = 0;

            unsigned int maxIndex = m_collisions.size()-1;
            for(unsigned int i = 0;i < m_collisions.size();i++){
                
                float closingVelocity = Collision::calculateClosingVelocity(&m_collisions[i]);

                //if(closingVelocity < max){
                if(abs(closingVelocity) > abs(max)){
                    
                    max = closingVelocity;
                    maxIndex = i;
                }

                
            }

                //resolve collision of largest closing velocity
                Collision::resolve(dt,&m_collisions[maxIndex]);

                m_iterationsUsed++;
            
        
        }
    }
}

void CollisionBatchResolver::registerContact(CollisionData collision){
    m_collisions.push_back(CollisionData(collision));
}

void CollisionBatchResolver::resetRegistry(){
    m_collisions.clear();
}

unsigned int CollisionBatchResolver::numOfCollisions(){
    return m_collisions.size();
}