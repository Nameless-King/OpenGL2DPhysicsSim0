#include "./Hitbox.h"

Hitbox::Hitbox():m_center(nullptr),m_scale(nullptr),m_hitboxType(HitboxType::NA){}

Hitbox::Hitbox(glm::vec3* center, glm::vec3* scale,const float* pvertices, HitboxType hitboxType)
	:m_center(center),
	m_scale(scale),
	m_halfExtent(glm::vec2(0.0f,0.0f)),
	m_hitboxType(hitboxType){
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

Hitbox::~Hitbox(){
}



