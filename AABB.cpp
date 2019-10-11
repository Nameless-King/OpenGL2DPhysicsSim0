#include "./AABB.h"

AABB::AABB():m_center(nullptr),m_scale(nullptr){}

AABB::AABB(glm::vec3* center, glm::vec3* scale,const float* pvertices)
	:m_center(center),
	m_scale(scale),
	m_halfExtent(glm::vec2(0.0f,0.0f)){
		
	int currentX = *(pvertices);
	int currentY = *(pvertices+1);
	for(int i = 2;i<8;i++){
		if(i%2==0){
			if(*(pvertices+i) != currentX){
				m_halfExtent.x = fabs(currentX-*(pvertices+i))/2.0f;
			}
				
		}else{
			if(*(pvertices+i) != currentY){
				m_halfExtent.y = fabs(currentY-*(pvertices+i))/2.0f;
			}
		}
	}
}

AABB::~AABB(){}

Collision AABB::getCollision(AABB box1, AABB box2){
	Collision collision;
	
	collision.distance = box1.getCenter() - box2.getCenter();
	collision.distance.x = fabs(collision.distance.x);
	collision.distance.y = fabs(collision.distance.y);
	
	glm::vec2 joinedExtents = box1.getHalfExtents() + box2.getHalfExtents();
	
	collision.distance = collision.distance - joinedExtents;
	
	collision.colliding = (collision.distance.x < 0 && collision.distance.y < 0);
	
	return collision;
}