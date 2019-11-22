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
		//collision.penetrationDepth = glm::vec2(0.0f,0.0f);
		collision.penetrationDepth = glm::length(joinedExtents-collision.distance);
	}else if(box1.getBBType() == BBType::Circle && box2.getBBType() == BBType::Circle){
		float joinedExtent = box1.getHalfExtents().x + box2.getHalfExtents().x;
		collision.colliding = (sqrt(pow(collision.distance.x,2.0f)+pow(collision.distance.y,2.0f)) < joinedExtent);
		//collision.penetrationDepth = glm::vec2(joinedExtent - collision.distance.x,joinedExtent-collision.distance.x);
		//collision.penetrationDepth = sqrt(pow(joinedExtent-collision.distance.x,2.0f)+pow(joinedExtent-collision.distance.y,2.0f));
		collision.penetrationDepth = glm::length(glm::vec2(joinedExtent,joinedExtent)-collision.distance);
	}
	
	if(collision.colliding){
		//normalize vector
		glm::vec2 distVector = box2.getCenter() - box1.getCenter();
		//float lengthDist = std::sqrt((collision.distance.x*collision.distance.x) + (collision.distance.y*collision.distance.y));
		//float lengthDist = glm::length(collision.distance);
		//if(lengthDist!=0){
			//collision.collisionNormal = glm::vec2(distVector.x/lengthDist,distVector.y/lengthDist);
			collision.collisionNormal = glm::normalize(distVector);
		//}else{
			//collision.collisionNormal = glm::vec2(1.0f,1.0f);
		//}
		  
	}

	
	
	return collision;
}

