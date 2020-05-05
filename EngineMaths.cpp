#include "./EngineMaths.h"

glm::vec2 EngineMaths::componentProduct(glm::vec2* a, glm::vec2* b){
	return glm::vec2(a->x*b->x,a->y*b->y);
}

glm::vec3 EngineMaths::componentProduct(glm::vec3* a, glm::vec3* b){
	return glm::vec3(a->x*b->x,a->y*b->y,a->z*b->z);
}

float EngineMaths::theta(glm::vec2* a, glm::vec2* b){
	float dotProd = glm::dot(*a,*b);
	float lengthProd = glm::length(*a) * glm::length(*b);
	return acos(dotProd/lengthProd);
}

float EngineMaths::theta(glm::vec3* a, glm::vec3* b){
	float dotProd = glm::dot(*a,*b);
	float lengthProd = glm::length(*a) * glm::length(*b);
	return acos(dotProd/lengthProd);
}

glm::mat2 EngineMaths::getRotationMatrix(float r){
	glm::mat2 rm(1.0f);

	rm[0][0] = cos((PI / 180.0) * r);
	rm[0][1] = -sin((PI / 180.0) * r);
	rm[1][0] = sin((PI / 180.0) * r);
	rm[1][1] = cos((PI / 180.0) * r);

	return rm;
}

 /*
    projection formula:
    proj of x onto l = (dot(l,x)/dot(l,l)) * x
    */
//projects vecot v onto axis l
glm::vec2 EngineMaths::projectOnto(glm::vec2 v, glm::vec2 l){
	return (glm::dot(v,l)/glm::dot(l,l)) * l;
}

glm::vec2 EngineMaths::absVec2(glm::vec2 v){
	return glm::vec2(abs(v.x),abs(v.y));
}

glm::vec2* EngineMaths::calcHalfExtents(const float* vertices, glm::vec3* scale){
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
				halfExtents->y = (fabs(currentY - *(vertices+i)) * scale->y)/2.0f;
			}
		}
	}

	return halfExtents;
}