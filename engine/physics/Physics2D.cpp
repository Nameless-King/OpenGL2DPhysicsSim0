#include "./Physics2D.h"

const static glm::vec2 gravity(0.0f,-10.0f);
const float Physics2D::G = 100.0f;

glm::vec2 Physics2D::getGravity(){
	return gravity;
}

void Physics2D::gravitate(glm::vec2 dir, float mag, Object* obj){
	
	glm::vec2 ray = dir-obj->getPositionXY();
	ray = glm::normalize(ray);
	glm::vec2 force = ray * mag;
	obj->getRigidbody2D()->addForce(force);
}

//Integrator of the physics engine
//Take not that the higher acceleration becomes to more unstable the physics
void Physics2D::integrate(Object* obj, float dt){
	//refer to updatePos for more comments
	glm::vec2 objPos(obj->getPositionXYZ().x,obj->getPositionXYZ().y);
	Rigidbody2D* objRb = obj->getRigidbody2D();
	glm::vec2 objVel(objRb->getVelocity()->x,objRb->getVelocity()->y);
	glm::vec2 objSigmaForce(objRb->getSigmaForce()->x,objRb->getSigmaForce()->y);
	glm::vec2 objAcl(objRb->getAcceleration()->x,objRb->getAcceleration()->y);
	
	objAcl += objRb->getInverseMass() * objSigmaForce;
	
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
	//objVel *= pow(objRb->getDamping(), dt);

	//update position
	objPos += dt*objVel;

	//not needed, the resulting value will by much too low to make a difference
	//objPos += dt*dt*0.5f*objRb->getAcceleration();


	
	objRb->setVelocity(objVel.x,objVel.y);
	obj->setPos(objPos.x,objPos.y);
	
	objRb->zeroForce();
}
