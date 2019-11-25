#include "./Physics2D.h"

const static glm::vec2 gravity(0.0f,-10.0f);
const float Physics2D::G = 100.0f;

glm::vec2 Physics2D::getGravity(){
	return gravity;
}

//Integrator of the physics engine
//Take not that the higher acceleration becomes to more unstable the physics
void Physics2D::updatePos(Object* obj){
	glm::vec2 objPos(obj->getPos().x,obj->getPos().y);
	RigidBody2D* objRb = obj->getRigidBody2D();
	glm::vec2 objVel(objRb->getVelocity()->x,objRb->getVelocity()->y);
	glm::vec2 objSigmaForce(objRb->getSigmaForce()->x,objRb->getSigmaForce()->y);
	glm::vec2 objAcl(objRb->getAcceleration()->x,objRb->getAcceleration()->y);
	float dt = ImGui::GetIO().DeltaTime;
	
	objAcl = objRb->getInverseMass() * objSigmaForce;
	
	//update velocity
	objVel += dt*objAcl;
	
	//damp velocity (like slowing it down to simulate drag)
	/*NOTE:
		-Taking the power of floats is large in computation time
		especially as the number of objects increase
		-Taking the power below is just to make the damping frame rate independent
			(prevent spikes in damping with variable framerate)
		-if trying to simulate many objects it is ok to ommit
		the power and just multiply velocity by the drag
		-though the smaller the damping value the more visible the spikes are
		when framerate dependent
	*/
	objVel *= pow(objRb->getDamping(), dt);
	
	//update position
	objPos += dt*objVel;
	
	//not needed, the resulting value will by much too low to make a difference
	//objPos += dt*dt*0.5f*objRb->getAcceleration();
	
	//objRb->setAcceleration(objAcl.x,objAcl.y);
	objRb->setVelocity(objVel.x,objVel.y);
	obj->setPos(objPos.x,objPos.y);
}

void Physics2D::integrator2(Object* obj, float dt){
	//refer to updatePos for more comments
	glm::vec2 objPos(obj->getPos().x,obj->getPos().y);
	RigidBody2D* objRb = obj->getRigidBody2D();
	glm::vec2 objVel(objRb->getVelocity()->x,objRb->getVelocity()->y);
	glm::vec2 objSigmaForce(objRb->getSigmaForce()->x,objRb->getSigmaForce()->y);
	glm::vec2 objAcl(objRb->getAcceleration()->x,objRb->getAcceleration()->y);
	
	
	objAcl += objRb->getInverseMass() * objSigmaForce;
	
	objVel += dt*objAcl;
	
	objVel *= pow(objRb->getDamping(), dt);
	
	objPos += dt*objVel;
	
	objRb->setVelocity(objVel.x,objVel.y);
	obj->setPos(objPos.x,objPos.y);
	
	objRb->zeroForce();

}

void Physics2D::gravitate(glm::vec2 dir, float mag, Object* obj){
	
	glm::vec2 ray = dir-obj->getPos2();
	ray = glm::normalize(ray);
	glm::vec2 force = ray * mag;
	obj->getRigidBody2D()->addForce(force);
}

void Physics2D::integrator3(Object* obj, float dt){
	//refer to updatePos for more comments
	glm::vec2 objPos(obj->getPos().x,obj->getPos().y);
	RigidBody2D* objRb = obj->getRigidBody2D();
	glm::vec2 objVel(objRb->getVelocity()->x,objRb->getVelocity()->y);
	glm::vec2 objSigmaForce(objRb->getSigmaForce()->x,objRb->getSigmaForce()->y);
	glm::vec2 objAcl(objRb->getAcceleration()->x,objRb->getAcceleration()->y);
	
	objAcl += objRb->getInverseMass() * objSigmaForce;
	
	objVel += dt*objAcl;
	
	objPos += dt*objVel;
	
	objRb->setVelocity(objVel.x,objVel.y);
	obj->setPos(objPos.x,objPos.y);
	
	objRb->zeroForce();
}

void Physics2D::updatePos(Object* object, float dt){
	object->getPos2() +=   dt * *(object->getRigidBody2D()->getVelocity());
}