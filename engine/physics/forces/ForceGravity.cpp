#include "./ForceGravity.h"

ForceGravity::ForceGravity(): 
m_gravity(glm::vec2(0.0f,1.0f)),
m_type(GravityType::Direction),
m_point(glm::vec2(0.0f,0.0f)),
m_magnitude(10.0f)
{}

ForceGravity::ForceGravity(const glm::vec2& gravity):
m_gravity(gravity),
m_type(GravityType::Direction),
m_point(glm::vec2(0.0f,0.0f)),
m_magnitude(10.0f){}

void ForceGravity::updateForce(Object* obj,float dt){
	if(obj->getRigidbody2D()->hasInfiniteMass()){
		return;
	}

	switch(m_type){
		case GravityType::Direction:
			{
			obj->getRigidbody2D()->addForce(m_gravity * obj->getRigidbody2D()->getMass());
			}
			break;
		case GravityType::Point:
			{
			std::cout << m_point.x << " " << m_point.y << std::endl;
			glm::vec2 direction = glm::vec2(0.0f) - obj->getPositionXY();
			direction = glm::normalize(direction) * m_magnitude;
			obj->getRigidbody2D()->addForce(direction);
			}
			break;
		default:
			std::cout << "unknown gravity type" << std::endl;
			break;
	}
}

void ForceGravity::setGravity(float gx, float gy){
	m_gravity.x = gx;
	m_gravity.y = gy;
}

void ForceGravity::setGravity(const glm::vec2 &gravity){
	m_gravity = gravity;
}

void ForceGravity::setPoint(glm::vec2 point, float mag){
	m_point = glm::vec2(glm::normalize(m_point));
	m_magnitude = mag;
}