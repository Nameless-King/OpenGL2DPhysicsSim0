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