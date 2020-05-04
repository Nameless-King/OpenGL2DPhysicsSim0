#include "./EngineMath.h"

glm::vec2 EngineMath::absVec2(const glm::vec2 v){
	return glm::vec2(abs(v.x),abs(v.y));
}

glm::vec2* EngineMath::calcHalfExtents(const float* vertices, glm::vec3* scale){
	int currentX = *(vertices);
	int currentY = *(vertices+1);
	glm::vec2* halfExtents = new glm::vec2(0.0f,0.0f);
	for(int i = 2;i<8;i++){
		if(i%2==0){
			if(*(vertices+i) != currentX){
				halfExtents->x = (fabs(currentX - *(vertices+i)) * scale->x)/2.0f;
			}
		}else{
			if(*(vertices+i) != currentY){
				halfExtents->y = (fabs(currentY - *(vertices+i)) * scale->x)/2.0f;
			}
		}
	}

	return halfExtents;
}

glm::vec2 EngineMath::componentProduct(const glm::vec2* a, const glm::vec2* b){
	return glm::vec2(a->x*b->x,a->y*b->y);
}

glm::vec3 EngineMath::componentProduct(const glm::vec3* a, const glm::vec3* b){
	return glm::vec3(a->x*b->x,a->y*b->y,a->z*b->z);
}


/*
	Projection formula
	proj of v onto l = (dot(l,v)/dot(l,l)) * v
*/
//uh oh, two different formulas which is correct?
glm::vec2 EngineMath::projectOnto(glm::vec2 v, glm::vec2 l){
	return (glm::dot(v,l)/glm::dot(l,l)) * l;
}

glm::mat2 EngineMath::rotationMatrix(float r){
	glm::mat2 rm(1.0f);
	
	rm[0][0] = cos((PI/180.0) * r);
	rm[0][1] = -sin((PI/180.0) * r);
	rm[1][0] = sin((PI/180.0) * r);
	rm[1][1] = cos((PI/180.0) * r);
	
	return rm;
}

float EngineMath::theta(const glm::vec2* a, const glm::vec2* b){
	float dotProd = glm::dot(*a,*b);
	float lengthProd = glm::length(*a) * glm::length(*b);
	return acos(dotProd/lengthProd);
}

float EngineMath::theta(const glm::vec3* a, const glm::vec3* b){
	float dotProd = glm::dot(*a,*b);
	float lengthProd = glm::length(*a) * glm::length(*b);
	return acos(dotProd/lengthProd);
}


