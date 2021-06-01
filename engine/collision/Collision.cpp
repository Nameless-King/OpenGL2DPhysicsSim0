#include "./Collision.h"

float Collision::calculateClosingVelocity(CollisionData* col) {
	glm::vec2 relativeVelocity = *(col->object[0]->getRigidbody2D()->getVelocity());
	if (col->object[1]) {
		relativeVelocity -= *(col->object[1]->getRigidbody2D()->getVelocity());
	}
	return glm::dot(relativeVelocity, col->collisionNormal);
}

//a and b must be of same bounding type for method
CollisionData Collision::calculateCollision(Object* a, Object* b) {
	CollisionData data;

	
	if(a->getBound()->getBoundingType() == BoundingType::AxisAligned && b->getBound()->getBoundingType() == BoundingType::Circle || a->getBound()->getBoundingType() == BoundingType::Circle && b->getBound()->getBoundingType() == BoundingType::AxisAligned){
		Object* circleObject;
		Object* aabbObject;
		if(a->getBound()->getBoundingType() == BoundingType::AxisAligned){
			aabbObject = a;
			circleObject = b;
						
		}else{
			circleObject = a;
			aabbObject = b;
		}
		data.object[0] = aabbObject;
		data.object[1] = circleObject;

		data.restitution = 0.0f;

		data.distance = *(data.object[1]->getBound()->getCenter()) - *(data.object[0]->getBound()->getCenter());
		data.distance.x = fabs(data.distance.x);
		data.distance.y = fabs(data.distance.y);

		glm::vec2 closest = data.distance;

		float aabbHalfExtentX = aabbObject->getBound()->getHalfExtents()->x;
		float aabbHalfExtentY = aabbObject->getBound()->getHalfExtents()->y;

		closest.x = std::clamp(closest.x, -aabbHalfExtentX,aabbHalfExtentX);
		closest.y = std::clamp(closest.y, -aabbHalfExtentY,aabbHalfExtentY);

		bool inside = false;

		if(data.distance == closest){
			inside = true;

			if(fabs(data.distance.x) > fabs(data.distance.y)){
				if(closest.x > 0){
					closest.x = aabbHalfExtentX;
				}else{
					closest.x = -aabbHalfExtentX;
				}
			}else{
				if(closest.y > 0){
					closest.y = aabbHalfExtentY;
				}else{
					closest.y = -aabbHalfExtentY;
				}
			}
		}

		glm::vec2 normal = data.distance - closest;
		float d = glm::length(normal) * glm::length(normal);
		float r = circleObject->getBound()->getHalfExtents()->x;

		if(d > (r * r) && !inside){
			/*
			Execution should never reach inside the
			if since it would mean the collision detection
			detected a collision but the collision
			resolution did not
			*/
			std::cout << "A COLLISION OCCURED BUT IT DIDN'T ???\n!!! FATAL !!!" << std::endl;
			data.object[0] = NULL;
			data.object[1] = NULL;
			return data;
		}
		
		d = glm::length(normal);

		//float tmpFloat = std::sqrt(std::pow(r-d,2.0f) / 2);

		if(inside){
			data.collisionNormal = normal / d;
			data.penetrationDepth = r-d;// glm::vec2(tmpFloat,tmpFloat);
		}else{
			data.collisionNormal = normal / d;
			data.penetrationDepth = r-d;//glm::vec2(tmpFloat,tmpFloat);
		}

		Collision::calculateAABBNormals(&data);

		// std::cout << "----COLLISION DATA----" << std::endl;
		// std::cout << data.object[0] << " " << data.object[1] << std::endl;
		// std::cout << "Distance: " << data.distance.x << " " << data.distance.y << std::endl;
		// std::cout << "Normal: " << data.collisionNormal.x << " " << data.collisionNormal.y << std::endl;
		// std::cout << "Penetration: " << glm::length(data.penetrationDepth) << std::endl;
		
		data.object[0] = a;
		data.object[1] = b;

		return data;
	}

	switch(a->getBound()->getBoundingType()){
		case BoundingType::AxisAligned:
		{
			data.distance = *(b->getBound()->getCenter()) - *(a->getBound()->getCenter());

			//TODO : is this fucking up everything
			//TODO : but is it though?
			data.distance.x = fabs(data.distance.x);
			data.distance.y = fabs(data.distance.y);

			glm::vec2 joinedExtents = *(a->getBound()->getHalfExtents()) + *(b->getBound()->getHalfExtents());

			glm::vec2 penetrationVector = joinedExtents - data.distance;
			data.penetrationDepth = ((penetrationVector.x > penetrationVector.y) ? penetrationVector.y : penetrationVector.x);


			data.object[0] = a;
            data.object[1] = b;

            data.restitution = 0.5f;

            Collision::calculateAABBNormals(&data);
		}
			break;
		case BoundingType::Circle:
		{
			glm::vec2 joinedExtents = *(a->getBound()->getHalfExtents()) + *(b->getBound()->getHalfExtents());

			data.distance = *(b->getBound()->getCenter()) - *(a->getBound()->getCenter());
			

			//something with needing different normals with infinite and finite mass 
			//circles (this doesn't make sense I just want it to work)
			if(!a->getRigidbody2D()->hasInfiniteMass() && !b->getRigidbody2D()->hasInfiniteMass()){
			data.collisionNormal = -data.distance / (glm::length(data.distance));
			} else{
				data.collisionNormal = data.distance / glm::length(data.distance);
			}

			//data.collisionNormal = -data.distance / glm::length(data.distance);

			data.distance.x = fabs(data.distance.x);
			data.distance.y = fabs(data.distance.y);

			data.penetrationDepth = glm::length(joinedExtents - data.distance);
			
			data.object[0] = a;
			data.object[1] = b;

			data.restitution = 0.5f;


		}

			break;
		case BoundingType::Oriented:{
			std::vector<glm::vec2> verts;

			/* must check GJK even if SAT is true
			 * if not then there will be sticking issues
			 */
			if(!Collision::GJKTest(a,b,&verts)){
				data.object[0] = NULL;
				data.object[1] = NULL;
				return data;
			}

			glm::vec2 penetrationVector = Collision::EPATest(verts);
			data.penetrationDepth = -glm::length(penetrationVector);
			//data.penetrationDepth = ((penetrationVector.x > penetrationVector.y) ? penetrationVector.y : penetrationVector.x);

			//prevents extreme case when point to face collision
			//i shouldn't use == since float but only works because of it
			if(penetrationVector.x < 0.00001f && penetrationVector.y == penetrationVector.x){
				data.object[0] = NULL;
				data.object[1] = NULL;
				return data;
			}

			data.distance = *(b->getBound()->getCenter()) - *(a->getBound()->getCenter());
			//data.distance.x = fabs(data.distance.x);
			//data.distance.y = fabs(data.distance.y);


			data.collisionNormal = glm::normalize(penetrationVector);

			data.object[0] = a;
			data.object[1] = b;
			data.restitution = 0.0f;
			
		}
			break;
		default:
			break;
	}
	return data;

}

void Collision::calculateAABBNormals(CollisionData* col){
	if(col->object[0]->getRigidbody2D()->hasInfiniteMass()){
        Object* temp = col->object[1];
        col->object[1] = col->object[0];
        col->object[0] = temp;
    }

    if(col->distance.x / (col->object[0]->getScaleXYZ().x * col->object[1]->getScaleXYZ().x) > col->distance.y / (col->object[0]->getScaleXYZ().y * col->object[1]->getScaleXYZ().y)){
        if(col->object[0]->getPositionXY().x > col->object[1]->getPositionXY().x){
			col->collisionNormal.x = 1;
			col->collisionNormal.y = 0;
		}else{
			col->collisionNormal.x = -1;
			col->collisionNormal.y = 0;
		}
    }else{
        if(col->object[0]->getPositionXY().y > col->object[1]->getPositionXY().y){
			col->collisionNormal.x = 0;
			col->collisionNormal.y = 1;
		}else{
			col->collisionNormal.x = 0;
			col->collisionNormal.y = -1;
		}
    }
}

bool Collision::isColliding(Bound* a, Bound* b) {
	bool isColliding = false;
	
	if(a == NULL && b == NULL){
		return isColliding;
	}
	

	glm::vec2 dist = *(b->getCenter()) - *(a->getCenter());
	dist.x = fabs(dist.x);
	dist.y = fabs(dist.y);

	glm::vec2 joinedExtents = *(b->getHalfExtents()) + *(a->getHalfExtents());

	if (a->getBoundingType() == b->getBoundingType()) {
		if (a->getBoundingType() == BoundingType::AxisAligned) {
			isColliding = dist.x < joinedExtents.x&& dist.y < joinedExtents.y;
		}
		else if (a->getBoundingType() == BoundingType::Circle) {
			float dotDist = glm::dot(dist, dist);
			//circles will have equal extents in x and y direction
			isColliding = dotDist <= joinedExtents.x * joinedExtents.x;
		}
		else if (a->getBoundingType() == BoundingType::Oriented) {
			OBB testA = (OBB)*a;
			OBB testB = (OBB)*b;
			isColliding = Collision::SATTest(&testA, &testB);
		}
	}else if( a->getBoundingType() == BoundingType::Circle && b->getBoundingType() == BoundingType::AxisAligned || a->getBoundingType() == BoundingType::AxisAligned && b->getBoundingType() == BoundingType::Circle){
		Bound* circleBound;
		Bound* aabbBound;
		if(a->getBoundingType() == BoundingType::Circle){
		circleBound = a;
		aabbBound = b;
		}else{
			circleBound = b;
			aabbBound = a;
		}

		// glm::vec2 distance = circleBound->getCopyCenterXY() - aabbBound->getCopyCenterXY();
		// glm::vec2 clamped = glm::clamp(distance, -*(aabbBound->getHalfExtents()),*(aabbBound->getHalfExtents()));
		// glm::vec2 closest = circleBound->getCopyCenterXY() + clamped;
		// distance = closest - circleBound->getCopyCenterXY();
		// isColliding = glm::length(distance) < circleBound->getHalfExtents()->x;
		glm::vec2 distance = *(circleBound->getCenter()) - *(aabbBound->getCenter());
		distance.x = fabs(distance.x);
		distance.y = fabs(distance.y);

		glm::vec2 closest = distance;

		float aabbHalfExtentX = aabbBound->getHalfExtents()->x;
		float aabbHalfExtentY = aabbBound->getHalfExtents()->y;

		closest.x = std::clamp(closest.x, -aabbHalfExtentX,aabbHalfExtentX);
		closest.y = std::clamp(closest.y, -aabbHalfExtentY,aabbHalfExtentY);

		bool inside = false;

		if(distance == closest){
			inside = true;

			if(fabs(distance.x) > fabs(distance.y)){
				if(closest.x > 0){
					closest.x = aabbHalfExtentX;
				}else{
					closest.x = -aabbHalfExtentX;
				}
			}else{
				if(closest.y > 0){
					closest.y = aabbHalfExtentY;
				}else{
					closest.y = -aabbHalfExtentY;
				}
			}
		}

		glm::vec2 normal = distance - closest;
		float d = glm::length(normal) * glm::length(normal);
		float r = circleBound->getHalfExtents()->x;

		if(d > (r * r) && !inside){
			inside = false;
		}else{
			inside = true;
		}

		isColliding = inside;
	}

	return isColliding;
}

void Collision::resolve(float dt, CollisionData* col) {
	if (correctObjects(col)) {
		float impulse = Collision::resolveVelocity(dt, col);
		//no for now there not broken or anything 
		//float impulse = Collision::resolveRestingContactVelocity(dt, col);

		Collision::resolveFriction(dt, impulse, col);
		
		//no for now there not broken or anything Collision::positionalCorrection(col);//exact same as resolveInterpenetration
		Collision::resolveInterpenetration(dt, col);
	}
}

void Collision::positionalCorrection(CollisionData* col) {
	float percent = 1.0f; //20 to 80 percent
	float slope = 0.1f; // 0.01 to 0.1

	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if (col->object[1]) {
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}



	//glm::vec2 correction = (std::max(Collision::getSmallestComponent(&col->penetrationDepth) - slope, 0.0f) / totalInverseMass) * percent * col->collisionNormal;
	glm::vec2 correction = (std::max(col->penetrationDepth - slope,0.0f) / totalInverseMass) * percent * col->collisionNormal;

	col->object[0]->setPos(col->object[0]->getPositionXY() + col->object[0]->getRigidbody2D()->getInverseMass() * correction);
	if (col->object[1]) {
		col->object[1]->setPos(col->object[1]->getPositionXY() - col->object[1]->getRigidbody2D()->getInverseMass() * correction);
	}


}

void Collision::resolveInterpenetration(float dt, CollisionData* col) {
	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if (col->object[1]) {
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}


	float penetration = col->penetrationDepth;
	//Below is 'false &&' since if block of code interferes with aabb vs circle
	if (false && col->object[0]->getBound()->getBoundingType() == BoundingType::Circle) {
		penetration =  col->object[0]->getBound()->getHalfExtents()->x * 2.0f - glm::length(col->distance);
	}
	//below line was used before line below it (idk why but the line below it works better with oriented bounding boxes
	glm::vec2 movePerMass = col->collisionNormal * (-penetration / totalInverseMass);
	if(col->object[0]->getBound()->getBoundingType() == BoundingType::AxisAligned || col->object[0]->getBound()->getBoundingType() == BoundingType::Circle){
		movePerMass = col->collisionNormal * (-col->penetrationDepth / totalInverseMass);
	}else if(col->object[0]->getBound()->getBoundingType() == BoundingType::Oriented){// || col->object[0]->getBound()->getBoundingType() == BoundingType::Circle){
		movePerMass = col->collisionNormal * (penetration / totalInverseMass);
	}
	movePerMass = col->collisionNormal * (-col->penetrationDepth / totalInverseMass);

	//affects the magnitude at which the interpenetration resolving affects the position
	//of the objects
	float percent = 1.0f; 
	//TODO : try and get rid of this (percent)
	//TODO : actually it looks important maybe don't get rid of it (percent)

	col->object[0]->setPos(col->object[0]->getPositionXY() + percent * -movePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if (col->object[1]) {
		col->object[1]->setPos(col->object[1]->getPositionXY() + percent * movePerMass * col->object[1]->getRigidbody2D()->getInverseMass());
	}
}

float Collision::getSmallestComponent(glm::vec2* vec) {
	return (vec->x < vec->y) ? vec->x : vec->y;
}


float Collision::resolveRestingContactVelocity(float dt, CollisionData* col) {
	
	float closingVelocity = Collision::calculateClosingVelocity(col);

	//separating collision (going in opposite directions)
	if (closingVelocity > 0) {
		return 0.0f;
	}

	float newClosingVelocity = -closingVelocity * col->restitution;

	glm::vec2 accCausedVelocity = *(col->object[0]->getRigidbody2D()->getAcceleration());
	if (col->object[1]) {
		accCausedVelocity -= *(col->object[1]->getRigidbody2D()->getAcceleration());
	}

	
	float accCausedClosingVelocity = glm::dot(accCausedVelocity, col->collisionNormal) * dt;

	//remove built up acceleration from new closing velocity
	if (accCausedClosingVelocity < 0) {
		newClosingVelocity += col->restitution * accCausedClosingVelocity;
		
		if (newClosingVelocity < 0) {
			newClosingVelocity = 0;
		}
	}

	float deltaVelocity = newClosingVelocity - closingVelocity;

	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if (col->object[1]) {
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}

	if (totalInverseMass <= 0) {
		return 0.0f;
	}

	float impulse = deltaVelocity / totalInverseMass;

	glm::vec2 impulsePerMass = col->collisionNormal * impulse;


	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + impulsePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if (col->object[1]) {
		//bruh dead a
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) + impulsePerMass * -col->object[1]->getRigidbody2D()->getInverseMass());
	}

	return impulse;
}


float Collision::resolveVelocity(float dt, CollisionData* col) {
	float closingVelocity = Collision::calculateClosingVelocity(col);
	if (closingVelocity > 0) {
		return 0;
	}

	float newClosingVelocity = -closingVelocity * col->restitution;
	float deltaVelocity = newClosingVelocity - closingVelocity;

	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if (col->object[1]) {
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}

	if (totalInverseMass <= 0) {
		return 0;
	}


	float impulse = deltaVelocity / totalInverseMass;

	glm::vec2 impulsePerMass = col->collisionNormal * impulse;

	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + impulsePerMass * col->object[0]->getRigidbody2D()->getInverseMass());
	if (col->object[1]) {
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) + impulsePerMass * -col->object[1]->getRigidbody2D()->getInverseMass());
	}

	return impulse;
}



void Collision::resolveFriction(float dt, float impulse, CollisionData* col) {
	glm::vec2 relativeVelocity = *(col->object[0]->getRigidbody2D()->getVelocity());
	if (col->object[1]) {
		relativeVelocity -= *(col->object[1]->getRigidbody2D()->getVelocity());
	}

	glm::vec2 frictionVector = relativeVelocity - glm::dot(relativeVelocity, col->collisionNormal) * col->collisionNormal;
	if (glm::length(frictionVector) > 0) {
		frictionVector = glm::normalize(frictionVector);
	}



	float frictionImpulse = -glm::dot(relativeVelocity, frictionVector);

	float totalInverseMass = col->object[0]->getRigidbody2D()->getInverseMass();
	if (col->object[1]) {
		totalInverseMass += col->object[1]->getRigidbody2D()->getInverseMass();
	}

	if (totalInverseMass <= 0) {
		return;
	}

	frictionImpulse = frictionImpulse / totalInverseMass;


	//TODO : if this method works find out how to make this changable
	float frictionCoefficient = 1.0f;

	glm::vec2 frictionImpulseVector;
	if (fabs(frictionImpulse) < impulse * frictionCoefficient) {
		frictionImpulseVector = frictionImpulse * frictionVector;
	}
	else {
		//idk if this works, not what example had
		frictionImpulseVector = -impulse * frictionVector * frictionCoefficient;
	}

	col->object[0]->getRigidbody2D()->setVelocity(*(col->object[0]->getRigidbody2D()->getVelocity()) + col->object[0]->getRigidbody2D()->getInverseMass() * frictionImpulseVector);
	if (col->object[1]) {
		col->object[1]->getRigidbody2D()->setVelocity(*(col->object[1]->getRigidbody2D()->getVelocity()) - col->object[1]->getRigidbody2D()->getInverseMass() * frictionImpulseVector);
	}
}

bool Collision::correctObjects(CollisionData* data) {
	if (data->object[0] && data->object[1]) {
		bool obj0InfMass = data->object[0]->getRigidbody2D()->hasInfiniteMass();
		bool obj1InfMass = data->object[1]->getRigidbody2D()->hasInfiniteMass();
		if (obj0InfMass && obj1InfMass) {
			return false;
		}
		if (obj0InfMass || obj1InfMass) {
			if (obj0InfMass) {
				data->object[0] = data->object[1];
				data->object[1] = NULL;
			}
			else {
				data->object[1] = NULL;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

bool Collision::SATTest(OBB* a, OBB* b) {
	glm::vec2 t = b->getCopyCenterXY() - a->getCopyCenterXY();

	//has to be negative rotations to line up with rendered object IDK why
	glm::mat2 a_rotMat = EngineMath::rotationMatrix(-a->getRotation());
	glm::mat2 b_rotMat = EngineMath::rotationMatrix(-b->getRotation());

	glm::vec2 curL = glm::normalize(a_rotMat * a->getLocalX());
	float curE = a->getHalfExtents()->x;

	float curW = b->getHalfExtents()->x;
	float curH = b->getHalfExtents()->y;
	glm::vec2 curX = b_rotMat * b->getLocalX();
	glm::vec2 curY = b_rotMat * b->getLocalY();

	bool colliding0 = fabs(glm::length(EngineMath::projectOnto(t, curL))) <
		curE
		+ fabs(glm::length(EngineMath::projectOnto(curW * curX, curL)))
		+ fabs(glm::length(EngineMath::projectOnto(curH * curY, curL)));

	if (!colliding0) {
		return 0;
	}

	curL = glm::normalize(a_rotMat * a->getLocalY());
	curE = a->getHalfExtents()->y;
	bool colliding1 = fabs(glm::length(EngineMath::projectOnto(t, curL))) <
		curE
		+ fabs(glm::length(EngineMath::projectOnto(curW * curX, curL)))
		+ fabs(glm::length(EngineMath::projectOnto(curH * curY, curL)));

	if (!colliding1) {
		return 0;
	}

	curL = glm::normalize(b_rotMat * b->getLocalX());
	curE = b->getHalfExtents()->x;
	curX = a_rotMat * a->getLocalX();
	curY = a_rotMat * a->getLocalY();
	curW = a->getHalfExtents()->x;
	curH = a->getHalfExtents()->y;
	bool colliding2 = fabs(glm::length(EngineMath::projectOnto(t, curL))) <
		curE
		+ fabs(glm::length(EngineMath::projectOnto(curW * curX, curL)))
		+ fabs(glm::length(EngineMath::projectOnto(curH * curY, curL)));

	if (!colliding2) {
		return 0;
	}

	curL = glm::normalize(b_rotMat * b->getLocalY());
	curE = b->getHalfExtents()->y;
	bool colliding3 = fabs(glm::length(EngineMath::projectOnto(t, curL))) <
		curE
		+ fabs(glm::length(EngineMath::projectOnto(curW * curX, curL)))
		+ fabs(glm::length(EngineMath::projectOnto(curH * curY, curL)));

	return colliding3;
}

glm::vec2 Collision::getSupport(Object* object, glm::vec2 direction) {
	if (object->getBound()->getBoundingType() == BoundingType::Circle) {
		//TODO : implement circle bound
		return glm::vec2(0.0f, 0.0f);
	}
	else {
		return EngineMath::polygonSupport(object->getGlobalVertices(), direction, object->getNumVertices() * 2);
	}
}

bool Collision::addSupport(Object* a, Object* b, glm::vec2 direction, std::vector<glm::vec2>* simplexVertices) {
	glm::vec2 newVertex = Collision::getSupport(a, direction) - Collision::getSupport(b, -direction);
	simplexVertices->push_back(newVertex);
	/*IDK why, even though the tutorial had only less than
	, the GJK collision test will only work if it's less than or
	equal to*/
	return glm::dot(direction, newVertex) >= 0;
}

SimplexStatus Collision::updateSimplex(std::vector<glm::vec2>* simplexVertices, Object* a, Object* b, glm::vec2* direction) {
	bool containsOrigin = false;
	switch (simplexVertices->size()) {
	case 0:
		*(direction) =b->getBound()->getCopyCenterXY() - a->getBound()->getCopyCenterXY();
		break;
	case 1:
		*(direction) *= -1;
		break;
	case 2: {
		glm::vec2 point1 = (*simplexVertices)[1];
		glm::vec2 point2 = (*simplexVertices)[0];

		glm::vec2 line21 = point1 - point2;
		glm::vec2 line20 = -point2;

		*(direction) = EngineMath::tripleCrossProduct(line21, line20, line21);
		break;
	}
	case 3: {
		//calc if simplex contains the origin
		glm::vec2 a = (*simplexVertices)[2];
		glm::vec2 b = (*simplexVertices)[1];
		glm::vec2 c = (*simplexVertices)[0];

		glm::vec2 a0 = -a; //v2 to origin
		glm::vec2 ab = b - a; //v2 to v1
		glm::vec2 ac = c - a;// v2 to v0

		glm::vec2 abPerp = EngineMath::tripleCrossProduct(ac, ab, ab);
		glm::vec2 acPerp = EngineMath::tripleCrossProduct(ab, ac, ac);

		if (glm::dot(abPerp, a0) > 0.0f) {
			//the origin is outside ab
			simplexVertices->erase(simplexVertices->begin());
			*(direction) = glm::vec2(abPerp);

		}
		else if (glm::dot(acPerp, a0) > 0.0f) {
			//the origin is outside ac
			simplexVertices->erase(simplexVertices->begin() + 1);
			*(direction) = glm::vec2(acPerp);

		}
		else {
			if (fabs(glm::dot(acPerp, a0)) < 0.000001f) {
				//they are touching but not intersecting
				return SimplexStatus::NotIntersecting;
			}
			else {
				//origin is inside both ab and ac (origin found in simplex)
				return SimplexStatus::AreIntersecting;
			}
			
		}

		break;
	}
	default:
		std::cout << "ERROR: 2D GJK test fourth vertex reached!" << std::endl;
		break;
	}
	SimplexStatus stat = Collision::addSupport(a, b, *(direction), simplexVertices) ? SimplexStatus::Searching : SimplexStatus::NotIntersecting;
	return stat;
}

//TODO : look at Minkowski Portal Refinement and how it compares to GJK
bool Collision::GJKTest(Object* a, Object* b, std::vector<glm::vec2>* simplexVertices) {
	glm::vec2 direction(0.0f, 0.0f);
	SimplexStatus status = SimplexStatus::Searching;
	while (status == SimplexStatus::Searching) {
		status = updateSimplex(
			simplexVertices,
			a,
			b,
			&direction
		);
	}
	//simplexVertices2 = simplexVertices;
	return status == SimplexStatus::AreIntersecting;
}

bool Collision::GJKTest2(Object* a, Object* b) {
	glm::vec2 direction(0.0f,0.0f);
	std::vector<float> simplexVertices;
	SimplexStatus status = SimplexStatus::Searching;
	while (status == SimplexStatus::Searching) {
		switch (simplexVertices.size()) {
		case 0: {
			Bound* boundB = b->getBound();
			Bound* boundA = a->getBound();
			direction = boundB->getCopyCenterXY() - boundA->getCopyCenterXY();
			break;
		}
		case 2:
			direction = -direction;
			break;
		case 4: {
			glm::vec2 point1(simplexVertices[2], simplexVertices[3]);
			glm::vec2 point2(simplexVertices[0], simplexVertices[1]);

			glm::vec2 line21 = point1 - point2;
			glm::vec2 line20 = -point2;

			direction = EngineMath::tripleCrossProduct(line21, line20, line21);
			break;
		}
		case 6: {
			//calc if simplex contains the origin
			glm::vec2 a(simplexVertices[4], simplexVertices[5]);
			glm::vec2 b(simplexVertices[2], simplexVertices[3]);
			glm::vec2 c(simplexVertices[0], simplexVertices[1]);

			glm::vec2 a0 = -a; //v2 to origin
			glm::vec2 ab = b - a; //v2 to v1
			glm::vec2 ac = c - a;// v2 to v0

			glm::vec2 abPerp = EngineMath::tripleCrossProduct(ac, ab, ab);
			glm::vec2 acPerp = EngineMath::tripleCrossProduct(ab, ac, ac);

			if (glm::dot(abPerp, a0) > 0.0f) {
				//the origin is outside ab
				simplexVertices.erase(simplexVertices.begin() + 1);
				simplexVertices.erase(simplexVertices.begin());

				direction = abPerp;

			}
			else if (glm::dot(acPerp, a0) > 0.0f) {
				//the origin is outside ac
				simplexVertices.erase(simplexVertices.begin() + 3);
				simplexVertices.erase(simplexVertices.begin() + 2);

				direction = acPerp;

			}
			else {
				//origin is inside both ab and ac
				status = SimplexStatus::AreIntersecting;
			}

			break;
		}
		default:
			std::cout << "ERROR: 2D GJK test fourth vertex reached!" << std::endl;
			break;
		}
		if (status != SimplexStatus::AreIntersecting) {
			glm::vec2 newVertex = Collision::getSupport(a, direction) - Collision::getSupport(b, -direction);
			simplexVertices.push_back(newVertex.x);
			simplexVertices.push_back(newVertex.y);
			status = glm::dot(direction, newVertex) >= 0.0f ? SimplexStatus::Searching : SimplexStatus::NotIntersecting;
		}

	}
	return status == SimplexStatus::AreIntersecting;
}

Edge Collision::findClosestEdge(std::vector<glm::vec2> polytopeVertices, RotatingDirection rotDir) {
	float closestDistance = INFINITY;
	int closestIndex = 0;

	glm::vec2 line;

	Edge closestEdge;
	closestEdge.distance = INFINITY;
	closestEdge.normal = glm::vec2(0.0f, 0.0f);
	closestEdge.index = 0;

	for (size_t i = 0; i < polytopeVertices.size(); i++) {
		size_t j = i + 1;

		if (j >= polytopeVertices.size()) {
			j = 0;
		}

		line = polytopeVertices[i] - polytopeVertices[j];

		glm::vec2 normal;
		switch (rotDir) {
		case RotatingDirection::Clockwise:
			normal = glm::vec2(line.y, -line.x);
			break;
		case RotatingDirection::CounterClockwise:
			normal = glm::vec2(-line.y, line.x);
			break;
		default:
			//this should never happen
			break;
		}
		normal = glm::normalize(normal);


		float dist = glm::dot(normal, polytopeVertices[i]);

		if (dist < closestDistance) {
			closestEdge.distance = dist;
			closestEdge.normal = normal;
			closestEdge.index = j;
		}


	}
	return closestEdge;
}

glm::vec2 Collision::EPATest(std::vector<glm::vec2>& simplexVertices) {
	RotatingDirection rotDir;
	float e0 = (simplexVertices[1].x - simplexVertices[0].x) * (simplexVertices[1].y + simplexVertices[0].y);
	float e1 = (simplexVertices[2].x - simplexVertices[1].x) * (simplexVertices[2].y + simplexVertices[1].y);
	float e2 = (simplexVertices[0].x - simplexVertices[2].x) * (simplexVertices[0].y + simplexVertices[2].y);
	if (e0 + e1 + e2 >= 0.0f) {
		rotDir = RotatingDirection::Clockwise;
	}
	else {
		rotDir = RotatingDirection::CounterClockwise;
	}

	glm::vec2 penetrationVector;
	for (int i = 0; i < 32; i++) {
		Edge edge = findClosestEdge(simplexVertices, rotDir);
		//claculate support
		float verts[] = {
			simplexVertices[0].x,simplexVertices[0].y,
			simplexVertices[1].x,simplexVertices[1].y,
			simplexVertices[2].x,simplexVertices[2].y
		};
		glm::vec2 support = EngineMath::polygonSupport(verts, edge.normal, sizeof(verts) / sizeof(float));
		float distance = glm::dot(support, edge.normal);

		penetrationVector = glm::vec2(edge.normal);
		penetrationVector *= distance;

		if (fabs(distance - edge.distance) <= 0.000001) {
			break;

		}
		else {
			simplexVertices.insert(simplexVertices.begin() + edge.index, support);
		}
	}

	return penetrationVector;
}


bool Collision::checkFlags(Object* a, Object* b){
	return (!a->getRigidbody2D()->hasInfiniteMass() || !b->getRigidbody2D()->hasInfiniteMass());
}

bool Collision::boundingVolumeTest(Object* a, Object* b){
	//precondition is that objects are of same boundingtype
	bool boundsColliding = true;

	BoundingType aType = a->getBound()->getBoundingType();

	if(aType != BoundingType::Circle && aType != BoundingType::AxisAligned){
		glm::vec2 distance = *(a->getBound()->getCenter()) - *(b->getBound()->getCenter());

		float extentTotal = a->getBound()->getFurthestDistance() + b->getBound()->getFurthestDistance();

		boundsColliding = glm::dot(distance, distance) <= extentTotal * extentTotal;
	}

	return boundsColliding;
}


