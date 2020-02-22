#include "./ObjectContact.h"

ObjectContact::ObjectContact(){}

ObjectContact::ObjectContact(const ObjectContact& contact){
    object[0] = contact.object[0];
    object[1] = contact.object[1];
    m_restitution = contact.m_restitution;
    m_contactNormal = contact.m_contactNormal;
    m_penetrationDepth = contact.m_penetrationDepth;
    m_distance = contact.m_distance;
    m_colliding = contact.m_colliding;
}



//currently in use in CollisionBatchResolver loop
void ObjectContact::resolve(float dt){


    if(correctObjects()){
        
        resolveVelocity(dt);
        //resolveRestingContactVelocity(dt);
        
        resolveInterpenetration(dt);
    }
   
}

void ObjectContact::resolveRestingContact(float dt){
    resolveRestingContactVelocity(dt);
    resolveInterpenetration(dt);
}


float ObjectContact::calculateClosingVelocity() const{
    glm::vec2 relativeVelocity = *(object[0]->getRigidBody2D()->getVelocity());
    if(object[1]){
        relativeVelocity -= *(object[1]->getRigidBody2D()->getVelocity());
    }
    return glm::dot(relativeVelocity,m_contactNormal);
}


void ObjectContact::resolveVelocity(float dt){
    //find velocity in direction of collision
    float closingVelocity = calculateClosingVelocity();

    //check whether needs to be resolved
    if(closingVelocity >0){
        //then no impulse required
        return;
    }

    //calc new closing velocity
    float newClosingVelcity = -closingVelocity * m_restitution;

    float deltaVelocity = newClosingVelcity - closingVelocity;

    //apply change in proportion to inverse mass
    float totalInverseMass = object[0]->getRigidBody2D()->getInverseMass();
    if(object[1] ){
        totalInverseMass += object[1]->getRigidBody2D()->getInverseMass();
    }

    if(totalInverseMass<=0){
        return;
    }

    //calc impulse
    float impulse = deltaVelocity / totalInverseMass;

    //find impulse per unit of inverse mass
    glm::vec2 impulsePerMass = m_contactNormal * impulse;

    //apply impulse in direction of contact
    //proportional to inverse mass
    object[0]->getRigidBody2D()->setVelocity(*(object[0]->getRigidBody2D()->getVelocity()) + impulsePerMass * object[0]->getRigidBody2D()->getInverseMass());
    if(object[1]){
        //object[1] goes in opposite direction
        object[1] -> getRigidBody2D()->setVelocity(*(object[1]->getRigidBody2D()->getVelocity()) + impulsePerMass * -object[1]->getRigidBody2D()->getInverseMass());
    }
}

void ObjectContact::resolveRestingContactVelocity(float dt){
    float closingVelocity = calculateClosingVelocity();

    //check whether needs to be resolved
    if(closingVelocity >0){
        //then no impulse required
        return;
    }

    //calc new closing velocity
    float newClosingVelocity = -closingVelocity * m_restitution;

    //check velocity due to acceleration only
    glm::vec2 accCausedVelocity = *(object[0]->getRigidBody2D()->getAcceleration());
    if(object[1]){
        accCausedVelocity -= *(object[1]->getRigidBody2D()->getAcceleration());
    }
    float accCausedClosingVelocity = glm::dot(accCausedVelocity, m_contactNormal) * dt;

    //remove built up acceleration from new closing velocity
    if(accCausedClosingVelocity < 0){
        
        newClosingVelocity += m_restitution * accCausedClosingVelocity;


        if(newClosingVelocity < 0){
            newClosingVelocity = 0;
        }
    }

    float deltaVelocity = newClosingVelocity - closingVelocity;

    float totalInverseMass = object[0]->getRigidBody2D()->getMass();
    if(object[1]){
        totalInverseMass += object[1]->getRigidBody2D()->getMass();
    }

    //for infinite mass implementation in the future
    if(totalInverseMass <= 0){
        return;
    }

    float impulse  = deltaVelocity / totalInverseMass;

    glm::vec2 impulsePerMass = m_contactNormal * impulse;

    object[0]->getRigidBody2D()->setVelocity(*(object[0]->getRigidBody2D()->getVelocity()) + impulsePerMass * object[0]->getRigidBody2D()->getInverseMass());
    if(object[1]){
        object[1]->getRigidBody2D()->setVelocity(*(object[1]->getRigidBody2D()->getVelocity()) + impulsePerMass * -object[1]->getRigidBody2D()->getInverseMass());
    }
}

void ObjectContact::resolveInterpenetration(float dt){
    if(m_penetrationDepth <= 0){
        return;
    }

     float totalInverseMass = object[0]->getRigidBody2D()->getInverseMass();
    if(object[1]){
         totalInverseMass += object[1]->getRigidBody2D()->getInverseMass();
     }

    glm::vec2 movePerMass = m_contactNormal * (-m_penetrationDepth/totalInverseMass);
    
    //affects the magnitude at which the interpenetration resolving affects the position
    //of the objects
    float percent = 1.0f;

     object[0]->setPos(object[0]->getPositionXY() + percent * -movePerMass * object[0]->getRigidBody2D()->getInverseMass());
    if(object[1]){
        object[1]->setPos(object[1]->getPositionXY() + percent * movePerMass * object[1]->getRigidBody2D()->getInverseMass());
     }
}

float ObjectContact::getSmallestComponent(glm::vec2 vector){
    return (vector.x < vector.y) ? vector.x : vector.y;
}

glm::vec2 ObjectContact::calcContactNormal(ObjectContact contact){
    glm::vec2 normal = (contact.m_distance.x < contact.m_distance.y) ? glm::vec2(1.0f,0.0f) : glm::vec2(0.0f,1.0f);
    return normal;
}

bool ObjectContact::isColliding(Hitbox box1, Hitbox box2){
    glm::vec2 dist = box2.getCenter() - box1.getCenter();
    dist.x = fabs(dist.x);
    dist.y = fabs(dist.y);
    if(box1.getHitboxType() == HitboxType::AxisAligned && box2.getHitboxType() == HitboxType::AxisAligned){
        glm::vec2 joinedExtents = box1.getHalfExtents() + box2.getHalfExtents();
        return (dist.x < joinedExtents.x && dist.y < joinedExtents.y);
    }else if(box1.getHitboxType() == HitboxType::Circle && box2.getHitboxType() == HitboxType::Circle){
        float joinedExtent = box1.getHalfExtents().x + box2.getHalfExtents().x;
        
        //alternative to prevent expensive sqrt()
        float dist2 = glm::dot(dist,dist);
        return dist2 <= joinedExtent * joinedExtent;
		
		//return (sqrt(pow(dist.x,2.0f)+pow(dist.y,2.0f)) < joinedExtent);
    }else{
        return false;
    }
}

ObjectContact ObjectContact::detectContact(Hitbox box1, Hitbox box2){
    
	ObjectContact contact;

	contact.m_distance = box2.getCenter() - box1.getCenter();
	
	contact.m_distance.x = fabs(contact.m_distance.x);
	contact.m_distance.y = fabs(contact.m_distance.y);

	if(box1.getHitboxType() == HitboxType::AxisAligned && box2.getHitboxType() == HitboxType::AxisAligned){
		glm::vec2 joinedExtents = box1.getHalfExtents() + box2.getHalfExtents();
		contact.m_colliding = (contact.m_distance.x < joinedExtents.x && contact.m_distance.y < joinedExtents.y);
		
		glm::vec2 penetrationVec = joinedExtents - contact.m_distance;
		contact.m_penetrationDepth = getSmallestComponent(penetrationVec);

		if(contact.m_colliding){
			contact.m_contactNormal = glm::normalize(box2.getCenter() - box1.getCenter());
		}

	}else if(box1.getHitboxType() == HitboxType::Circle && box2.getHitboxType() == HitboxType::Circle){
		float joinedExtent = box1.getHalfExtents().x + box2.getHalfExtents().x;
        
        //alternative to prevent expensive sqrt()
        float dist2 = glm::dot(contact.m_distance,contact.m_distance);
        contact.m_colliding = dist2 <= joinedExtent * joinedExtent;
		
        //contact.m_colliding = (sqrt(pow(contact.m_distance.x,2.0f)+pow(contact.m_distance.y,2.0f)) < joinedExtent);

		glm::vec2 penetrationVec = glm::vec2(joinedExtent,joinedExtent)-contact.m_distance;
		contact.m_penetrationDepth = getSmallestComponent(penetrationVec);
		if(contact.m_colliding){
			glm::vec2 distVector = box2.getCenter() - box1.getCenter();
			contact.m_contactNormal = glm::normalize(distVector);
		}
	}
	
	return contact;
}



bool ObjectContact::correctObjects(){
    if(object[0] && object[1]){
         if(hasInfiniteMass(object[0]) && hasInfiniteMass(object[1])){
        return false;
        }
    
        if(hasInfiniteMass(object[0]) || hasInfiniteMass(object[1])){
            if(hasInfiniteMass(object[0])){
                object[0] = object[1];
                object[1] = NULL;
            }else{
                object[1] = NULL;
            }
        }
    }
   
    return true;
}

bool ObjectContact::hasInfiniteMass(Object* argObj){
    return argObj->getRigidBody2D()->getMass() < 0;
}