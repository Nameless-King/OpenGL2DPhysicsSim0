#include "./EngineMath.h"

glm::vec2 EngineMath::absVec2(const glm::vec2 v){
	return glm::vec2(abs(v.x),abs(v.y));
}

glm::vec2* EngineMath::calcHalfExtents(const float* vertices, glm::vec2* scale){
	int currentX = (int) *(vertices);
	int currentY = (int) *(vertices+1);
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
	
	rm[0][0] = (float) cos((PI/180.0) * r);
	rm[0][1] = (float) -sin((PI/180.0) * r);
	rm[1][0] = (float) sin((PI/180.0) * r);
	rm[1][1] = (float) cos((PI/180.0) * r);
	
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

glm::vec2 EngineMath::circleSupport(glm::vec2 center, float radius, glm::vec2 direction){
	return center + radius * glm::normalize(direction);
}

//returns the furthest point of a polygon in a given direction
glm::vec2 EngineMath::polygonSupport(const float* vertices, glm::vec2 direction,int arraySize){
	float distance = -INFINITY;
	glm::vec2 vertex(0.0f,0.0f);

	for(int i=0;i<arraySize;i+=2){
		glm::vec2 currentVertex(*(vertices+i),*(vertices+i+1));

		float currentDistance = glm::dot(currentVertex,direction);

		if(currentDistance > distance){
			distance = currentDistance;
			vertex = glm::vec2(currentVertex);
		}
	}
	return glm::vec2(vertex);
}

glm::vec2 EngineMath::tripleCrossProduct(glm::vec2 a,glm::vec2 b,glm::vec2 c){
	return b * glm::dot(a,c) - a * glm::dot(b,c);
}

float EngineMath::leastPenetrationAxis(const float* a_vertices, const float* b_vertices, int a_size, int b_size){
	float bestPenetration = -INFINITY;

	for(int i = 0;i<a_size;i+=4){
		glm::vec2 currentVertex1(*(a_vertices+i),*(a_vertices+i+1));
		glm::vec2 currentVertex2(*(a_vertices+i+2),*(a_vertices+i+3));
		glm::vec2 a_faceNormal = calcFaceNormal(currentVertex1.x,currentVertex1.y,currentVertex2.x,currentVertex2.y);

		glm::vec2 s = polygonSupport(b_vertices,-a_faceNormal,b_size);

		float penDist = glm::dot(a_faceNormal,s - currentVertex1);

		if(penDist > bestPenetration){
			bestPenetration = penDist;
		}
	}
	return bestPenetration;
}

glm::vec2 EngineMath::calcMidpoint(float x1, float y1, float x2, float y2){
	return glm::vec2((x1 + x2) / 2.0f,(y1 + y2)/2.0f);
}

glm::vec2 EngineMath::calcFaceNormal(float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;

	//normals are (-dy, dx) and (dy, -dx)

	return glm::vec2(dy,-dx);
}

float EngineMath::calcCircleInertia(float mass, float radius){
	return 0.5f * mass * radius * radius;
}

float EngineMath::calcPolygonInertia(float density, const float* vertices, int size){
	float inertia = 0.0f;
	for(int i = 0;i<size;i+=4){
		glm::vec2 faceVertex1(*(vertices+i),*(vertices+i+1));
		glm::vec2 faceVertex2(*(vertices+i+2),*(vertices+i+3));
		float crossProd = faceVertex1.x * faceVertex2.y - faceVertex1.y * faceVertex2.x;
		float partMass = density * 0.5f * abs(crossProd);
		float v1SquaredLength = faceVertex1.x * faceVertex1.x + faceVertex1.y * faceVertex1.y;
		float v2SquaredLength = faceVertex2.x * faceVertex2.x + faceVertex2.y * faceVertex2.y;
		float partInertia = partMass * (v1SquaredLength + v2SquaredLength + glm::dot(faceVertex1,faceVertex2)) / 6.0f;
		inertia += partInertia;
	}
	return inertia;
}

float EngineMath::minPointToLineDistance(float p1, float p2, float x1, float y1, float x2, float y2){
	float m = (y2 - y1) / (x2 - x1);
	float b = y1 - (x1 * m);

	return 0.0f;
}
