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
				halfExtents->y = (fabs(currentY - *(vertices+i)) * scale->y)/2.0f;
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

glm::mat2 EngineMath::rotationMatrixRadians(float r){
	glm::mat2 rm(1.0f);
	rm[0][0] = cos(r);
	rm[0][1] = -sin(r);
	rm[1][0] = sin(r);
	rm[1][1] = cos(r);

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

float EngineMath::calcRectInertia(float mass, float width, float height){
	return mass * (width * width + height * height) / 12.0f;
}


glm::vec2 EngineMath::circleSupport(glm::vec2 center, float radius, glm::vec2 direction){
	return center + radius * glm::normalize(direction);
}

glm::vec2 EngineMath::polygonSupport(const float* vertices, glm::vec2 direction){
	float distance = -INFINITY;
	glm::vec2 vertex;

	for(int i=0;i<8;i+=2){
		glm::vec2 currentVertex(*(vertices+i),*(vertices+i+1));

		float currentDistance = glm::dot(currentVertex,direction);

		if(currentDistance > distance){
			distance = currentDistance;
			vertex = currentVertex;
		}
	}
	return vertex;
}

glm::vec2 EngineMath::tripleCrossProduct(glm::vec2 a,glm::vec2 b,glm::vec2 c){
	return b * glm::dot(a,c) - a * glm::dot(b,c);
	/*
	glm::vec3 a3(a.x,a.y,0.0f);
	glm::vec3 b3(b.x,b.y,0.0f);
	glm::vec3 c3(c.x,c.y,0.0f);

	glm::vec3 first = glm::cross(a3,b3);
	glm::vec3 second = glm::cross(first,c3);

	return glm::vec2(second.x,second.y);
	*/
	
}

