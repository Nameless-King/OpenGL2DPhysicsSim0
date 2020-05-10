#include "./Collision.h"

float Collision::calculateClosingVelocity( CollisionData* col) {
	glm::vec2 relativeVelocity = *(col->object[0]->getRigidbody2D()->getVelocity());
	if(col->object[1]){
		relativeVelocity -= *(col->object[1]->getRigidbody2D()->getVelocity());
	}
	return glm::dot(relativeVelocity,col->collisionNormal);
}

CollisionData Collision::calculateCollision( Bound* a,  Bound* b){
	CollisionData data;

	data.distance = *(b->getCenter()) - *(a->getCenter());
	
	//TODO : is this fucking up everything
	//TODO : but is it though?
	data.distance.x = fabs(data.distance.x);
	data.distance.y = fabs(data.distance.y);
	
	glm::vec2 joinedExtents = *(a->getHalfExtents()) + *(b->getHalfExtents());

	//TODO : original code takes smallest component
	data.penetrationDepth = joinedExtents - data.distance;
	
	//TODO : above TODO if corrected will result in below simplification
	data.collisionNormal = glm::normalize(*(b->getCenter()) - *(a->getCenter()));
	
	return data;
}

bool Collision::isColliding( Bound* a,  Bound* b){
	bool isColliding = false;

	glm::vec2 dist = *(b->getCenter()) - *(a->getCenter());
    dist.x = fabs(dist.x);
    dist.y = fabs(dist.y);
	
	glm::vec2 joinedExtents = *(b->getHalfExtents()) + *(a->getHalfExtents());
	
	if(a->getBoundingType() == b->getBoundingType()){
		if(a->getBoundingType() == BoundingType::AxisAligned){
			isColliding = dist.x < joinedExtents.x && dist.y < joinedExtents.y;
		}else if(a->getBoundingType() == BoundingType::Circle){
			float dotDist = glm::dot(dist,dist);
			//circles will have equal extents in x and y direction
			isColliding = dotDist <= joinedExtents.x * joinedExtents.x;
		}else if(a->getBoundingType() == BoundingType::Oriented){
			OBB testA = (OBB)*a;
			OBB testB = (OBB)*b;
			isColliding = Collision::SATTest(&testA,&testB);
		}
	}
	
	return isColliding;
}

void Collision::resolve(float dt,CollisionData* col){
	if(correctObjects(col)){
		float impulse = Collision::resolveVelocity(dt, col);
		Collision::resolveFriction(dt,impulse,col);
		//Collision::resolveRestingContactVelocity(dt);
		Collision::resolveInterpenetration(dt,col);
	}
}

void Collision::resolveInterpenetration(float dt, CollisionData* col){
	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if(col->object[1]){
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}
	
	glm::vec2 movePerMass = col->collisionNormal * (-getSmallestComponent(&col->penetrationDepth)/totalInverseMass);
	
	//affects the magnitude at which the interpenetration resolving affects the position
	//of the objects
	float percent = 1.0f; //TODO : try and get rid of this
	
	col->object[0]->setPos(col->object[0]->getPositionXY() + percent * -movePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if(col->object[1]){
		col->object[1]->setPos(col->object[1]->getPositionXY() + percent * movePerMass * col->object[1]->getRigidbody2D()->getInverseMass());
	}
}

float Collision::getSmallestComponent(glm::vec2* vec){
	return (vec->x < vec->y) ? vec->x : vec->y;
}

void Collision::resolveRestingContactVelocity(float dt, CollisionData* col){
	float closingVelocity = Collision::calculateClosingVelocity(col);
	
	if(closingVelocity > 0){
		return;
	}
	
	float newClosingVelocity = -closingVelocity * col->restitution;
	
	glm::vec2 accCausedVelocity = *(col->object[0]->getRigidbody2D()->getAcceleration());
	if(col->object[1]){
		accCausedVelocity -= *(col->object[1]->getRigidbody2D()->getAcceleration());
	}
	
	float accCausedClosingVelocity = glm::dot(accCausedVelocity,col->collisionNormal) * dt;
	
	//remove built up acceleration from new closing velocity
	if(accCausedClosingVelocity < 0){
		newClosingVelocity += col->restitution * accCausedClosingVelocity;
		
		if(newClosingVelocity < 0){
			newClosingVelocity = 0;
		}
	}
	
	float deltaVelocity = newClosingVelocity - closingVelocity;
	
	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if(col->object[1]){
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}
	
	if(totalInverseMass <= 0){
		return;
	}
	
	float impulse = deltaVelocity / totalInverseMass;
	
	glm::vec2 impulsePerMass = col->collisionNormal * impulse;
	
	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + impulsePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if(col->object[1]){
		//bruh dead a
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) + impulsePerMass * -col->object[1]->getRigidbody2D()->getInverseMass());
	}
}

float Collision::resolveVelocity(float dt, CollisionData* col){
	float closingVelocity = Collision::calculateClosingVelocity(col);
	
	if(closingVelocity > 0){
		return 0;
	}
	
	float newClosingVelocity = -closingVelocity * col->restitution;
	float deltaVelocity = newClosingVelocity - closingVelocity;
	
	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if(col->object[1]){
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}
	
	if(totalInverseMass <= 0){
		return 0;
	}
	
	float impulse = deltaVelocity / totalInverseMass;
	
	glm::vec2 impulsePerMass = col->collisionNormal * impulse;
	
	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + impulsePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if(col->object[1]){
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) + impulsePerMass * -col->object[1]->getRigidbody2D()->getInverseMass());
	}

	return impulse;
}

void Collision::resolveFriction(float dt, float impulse, CollisionData* col){
	glm::vec2 relativeVelocity = *(col->object[0]->getRigidbody2D()->getVelocity());
	if(col->object[1]){
		relativeVelocity -= *(col->object[1]->getRigidbody2D()->getVelocity());
	}

	glm::vec2 frictionVector = relativeVelocity - glm::dot(relativeVelocity,col->collisionNormal) * col->collisionNormal;
	if(glm::length(frictionVector) > 0){
		frictionVector = glm::normalize(frictionVector);
	}
	
	

	float frictionImpulse = -glm::dot(relativeVelocity,frictionVector);
	
	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if(col->object[1]){
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}
	
	if(totalInverseMass <= 0){
		return;
	}

	frictionImpulse = frictionImpulse / totalInverseMass;
	

	//TODO : if this method works find out how to make this changable
	float frictionCoefficient = 0.5f;

	glm::vec2 frictionImpulseVector;
	if(fabs(frictionImpulse) < impulse * frictionCoefficient){
		frictionImpulseVector = frictionImpulse * frictionVector;
	}else{
		//idk if this works, not what example had
		frictionImpulseVector = -impulse * frictionVector * frictionCoefficient;
	}

	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + col->object[0]->getRigidbody2D()->getInverseMass() * frictionImpulseVector);
	if(col->object[1]){
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) + col->object[1]->getRigidbody2D()->getInverseMass() * frictionImpulseVector);
	}
}

bool Collision::correctObjects(CollisionData* data){
	if(data->object[0] && data->object[1]){
		bool obj0InfMass = data->object[0]->getRigidbody2D()->hasInfiniteMass();
		bool obj1InfMass = data->object[1]->getRigidbody2D()->hasInfiniteMass();
		if(obj0InfMass && obj1InfMass){
			return false;
		}
		if(obj0InfMass || obj1InfMass){
			if(obj0InfMass){
				data->object[0] = data->object[1];
				data->object[1] = NULL;
			} else {
				data->object[1] = NULL;
			}
		}
	}else{
		return false;
	}
	return true;
}

bool Collision::SATTest( OBB* a,  OBB* b){
	glm::vec2 t = EngineMath::absVec2(b->getCopyCenterXY() - a->getCopyCenterXY());

    glm::mat2 a_rotMat = EngineMath::rotationMatrix(a->m_rotation);
    glm::mat2 b_rotMat = EngineMath::rotationMatrix(b->m_rotation);
    
    glm::vec2 curL = glm::normalize(a_rotMat * a->m_localX);
    float curE = a->m_halfExtents->x;

    float curW = b->m_halfExtents->x;
    float curH = b->m_halfExtents->y;
    glm::vec2 curX = glm::normalize(b_rotMat * b->m_localX);
    glm::vec2 curY = glm::normalize(b_rotMat * b->m_localY);

    bool colliding0 = (glm::length(EngineMath::projectOnto(t,curL))) <
        curE 
        + (glm::length(EngineMath::projectOnto(curW  *curX,curL)))
        + (glm::length(EngineMath::projectOnto(curH * curY,curL)));

    curL =  glm::normalize(a_rotMat * a->m_localY);
    curE = a->m_halfExtents->y;
    bool colliding1 = glm::length(EngineMath::projectOnto(t,curL)) <
        curE
        + glm::length(EngineMath::projectOnto(curW * curX,curL))
        + glm::length(EngineMath::projectOnto(curH * curY,curL));

    curL = glm::normalize(b_rotMat * b->m_localX);
    curE = b->m_halfExtents->x;
    curX =  glm::normalize(a_rotMat * a->m_localX);
    curY =  glm::normalize(a_rotMat * a->m_localY);
    curW = a->m_halfExtents->x;
    curH = a->m_halfExtents->y;
    bool colliding2 = glm::length(EngineMath::projectOnto(t,curL)) <
        curE
        + glm::length(EngineMath::projectOnto(curW * curX,curL))
        + glm::length(EngineMath::projectOnto(curH * curY,curL));

    curL = glm::normalize(b_rotMat * b->m_localY);
    curE = b->m_halfExtents->y;
    bool colliding3 = glm::length(EngineMath::projectOnto(t,curL)) <
        curE
        + glm::length(EngineMath::projectOnto(curW * curX,curL))
        + glm::length(EngineMath::projectOnto(curH * curY,curL));

	return colliding0 && colliding1 && colliding2 && colliding3;
}



