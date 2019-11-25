#include "./AABB.h"

AABB::AABB():m_center(nullptr),m_scale(nullptr),m_bbType(BBType::NA){}

AABB::AABB(glm::vec3* center, glm::vec3* scale,const float* pvertices, BBType bbType)
	:m_center(center),
	m_scale(scale),
	m_halfExtent(glm::vec2(0.0f,0.0f)),
	m_bbType(bbType){
	int currentX = *(pvertices);
	int currentY = *(pvertices+1);
	for(int i = 2;i<8;i++){
		if(i%2==0){
			if(*(pvertices+i) != currentX){
				m_halfExtent.x = (fabs(currentX-*(pvertices+i)) * m_scale->x)/2.0f;
			}
				
		}else{
			if(*(pvertices+i) != currentY){
				m_halfExtent.y = (fabs(currentY-*(pvertices+i))*m_scale->y)/2.0f;
			}
		}
	}
}

AABB::~AABB(){
}

Collision AABB::getCollision(AABB box1, AABB box2){

	Collision collision;

	collision.distance = box1.getCenter() - box2.getCenter();
	
	collision.distance.x = fabs(collision.distance.x);
	collision.distance.y = fabs(collision.distance.y);

	if(box1.getBBType() == BBType::AxisAligned && box2.getBBType() == BBType::AxisAligned){
		glm::vec2 joinedExtents = box1.getHalfExtents() + box2.getHalfExtents();
		//collision.distance = collision.distance - joinedExtents;
		collision.colliding = (collision.distance.x < joinedExtents.x && collision.distance.y < joinedExtents.y);
		
		glm::vec2 penetrationVec = joinedExtents - collision.distance;
		collision.penetrationDepth = getSmallestComponent(penetrationVec);

		if(collision.colliding){
			collision.collisionNormal = glm::normalize(box2.getCenter() - box1.getCenter());
			//collision.collisionNormal = getAABBCollisionNormal(collision);
		}

	}else if(box1.getBBType() == BBType::Circle && box2.getBBType() == BBType::Circle){
		float joinedExtent = box1.getHalfExtents().x + box2.getHalfExtents().x;
		collision.colliding = (sqrt(pow(collision.distance.x,2.0f)+pow(collision.distance.y,2.0f)) < joinedExtent);
		glm::vec2 penetrationVec = glm::vec2(joinedExtent,joinedExtent)-collision.distance;
		collision.penetrationDepth = getSmallestComponent(penetrationVec);
		if(collision.colliding){
			glm::vec2 distVector = box2.getCenter() - box1.getCenter();
			collision.collisionNormal = glm::normalize(distVector);
		}
	}
	
	return collision;
}

float AABB::getSmallestComponent(glm::vec2 vector){
	return (vector.x < vector.y) ? vector.x : vector.y;
}

glm::vec2 AABB::getAABBCollisionNormal(Collision collision){
	glm::vec2 normal = (collision.distance.x < collision.distance.y) ? glm::vec2(1.0f,0.0f) : glm::vec2(0.0f,1.0f);
	return glm::vec2(0.0f,1.0f);
}

