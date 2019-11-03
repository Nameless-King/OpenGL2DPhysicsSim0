#include "./Physics2D.h"

const static glm::vec2 gravity(0.0f,-9.8f);

void Physics2D::resolveCollision(Object* a, Object* b, Collision collision){

	
	//relative velocity
	glm::vec2 rv =  b->getBoundingBox().getCenter() - a->getBoundingBox().getCenter();
	//glm::vec2(b->getPos().x,b->getPos().y) - glm::vec2(a->getPos().x,a->getPos().y);
	
	//rv.x = fabs(rv.x);
	//rv.y = fabs(rv.y);

	
	//calculate relative velocity in terms of the normal direction
	float velNormal = rv.x * collision.collisionNormal.x + rv.y * collision.collisionNormal.y;
	
	
	
	if(velNormal > 0){
		return;
	}
	
	//calculate restitution
	float e = std::min(a->getRestitution(),b->getRestitution());
	
	//calculate impulse scalar
	float j = -(1 + e) * velNormal;
	j /= 1 / a->getMass() + 1/ b->getMass();
	
	//apply impulse
	glm::vec2 impulse = j * collision.collisionNormal;
	
	glm::vec2 resultingAVel = a->getVelocity() + 1 / a->getMass() * impulse;
	glm::vec2 resultingBVel = b->getVelocity() - 1 / b->getMass() * impulse;
    
	a->setVelocity(resultingAVel.x,resultingAVel.y);
	b->setVelocity(resultingBVel.x,resultingBVel.y);
}

void Physics2D::positionalCorrection(Object* a, Object* b,Collision collision){
	const float percent = 0.1f; //usually 20% to 80% (penetration percentage to correct)
	const float slop = 0.1f; //usually 0.01 to 0.1 (penetration allowance)
	glm::vec2 correction = std::max(collision.penetrationDepth - slop,0.0f)/((1.0f/a->getMass()) + (1.0f/b->getMass())) * percent * collision.collisionNormal;
	
	
	//(collision.penetrationDepth/(1.0/a->getMass() + 1.0/b->getMass())*percent) * collision.collisionNormal;
	
	assert(a->getMass() != 0);
	assert(b->getMass() != 0);

	glm::vec2 correctionA = a->getBoundingBox().getCenter();
	float inverseA = (1.0f/a->getMass());
	correctionA -= glm::vec2(correction.x*inverseA,correction.y*inverseA);
	
	glm::vec2 correctionB = b->getBoundingBox().getCenter();
	float inverseB = (1.0f/b->getMass());
	correctionB += glm::vec2(correction.x*inverseB,correction.y*inverseB);
	
	//glm::vec2 correctionA = a->getBoundingBox().getCenter() - ((1.0/a->getMass()) * correction);
	//glm::vec2 correctionB = b->getBoundingBox().getCenter() + (1.0/b->getMass()) * correction;
	
	
	
	//glm::vec2 correctionA = glm::vec2(a->getPos().x,a->getPos().y) - (1.0f,a->getMass()) * glm::vec2(1.0f,1.0f);
	//glm::vec2 correctionB = glm::vec2(b->getPos().x,b->getPos().y) + (1.0f,b->getMass()) * glm::vec2(1.0f,1.0f);
	
	a->setPos(correctionA.x,correctionA.y,0.0f);
	b->setPos(correctionB.x,correctionB.y,0.0f);
}

glm::vec2 Physics2D::getGravity(){
	return gravity;
}


//Take not that the higher acceleration becomes to more unstable the physics
void Physics2D::updatePos(Object* obj){
	glm::vec2 objPos(obj->getPos().x,obj->getPos().y);
	RigidBody2D* objRb = obj->getRigidBody2D();
	glm::vec2 objVel(objRb->getVelocity()->x,objRb->getVelocity()->y);
	glm::vec2 objAcl(objRb->getAcceleration()->x,objRb->getAcceleration()->y);
	float dt = ImGui::GetIO().DeltaTime;
	
	//update velocity
	objVel += dt*objAcl;
	
	//damp velocity (like slowing it down to simulate drag)
	objVel *= pow(objRb->getDamping(), dt);
	
	//update position
	objPos += dt*objVel;
	
	//not needed, the resulting value will by much too low to make a difference
	//objPos += dt*dt*0.5f*objRb->getAcceleration();
	
	objRb->setVelocity(objVel.x,objVel.y);
	obj->setPos(objPos.x,objPos.y);
}
