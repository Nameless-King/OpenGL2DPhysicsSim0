#pragma once

#include <iostream>
#include "../../Dependencies/glm/glm.hpp"

#define PI 3.14159265358979

/*The following calculations are provided by glm:
	-cross (3D ONLY)
	-distance
	-dot
	-length (magnitude)
	-reflect
	-refract
*/

/* Notes:
	-) a x b != b x a (cross)(3D ONLY)
	-) a x b = -b x a (cross)(3D ONLY)
	-) a o b = b o a (componentProduct)
	-) a * b = b * a (scalar)
	-)scaledVector = this + v * s 
*/

/* Formulas:
	-) p_prime = p + deriv1_p * t; (for object not accelerating)
	-) deriv1_p_prime = deriv1_p + deriv2_p * t;
	-) p_prime = p + deriv1_p * t + deriv2_p * (t^2) / 2; (finding position if accelerating constantly)
*/

class EngineMath{
	public:
		//returns furthest point in a direction on a given circle
		static glm::vec2 circleSupport(glm::vec2 center, float radius, glm::vec2 direction); 
		//returns furthest point in a direction from the given vertices
		static glm::vec2 polygonSupport(const float* vertices, glm::vec2 direction, int arraySize); 
		static glm::vec2 absVec2(const glm::vec2 v); 
		static glm::vec2* calcHalfExtents(const float* vertices,glm::vec2* scale); 
		static glm::vec2 componentProduct(const glm::vec2* a, const glm::vec2* b); 
		static glm::vec3 componentProduct(const glm::vec3* a, const glm::vec3* b);
		static glm::vec2 projectOnto(glm::vec2 v, glm::vec2 l); 
		static glm::mat2 rotationMatrix(float r); 
		static glm::mat2 rotationMatrixRadians(float r); 
		//theta returns the angle between two vectors
		static float theta(const glm::vec2* a, const glm::vec2* b); 
		static float theta(const glm::vec3* a, const glm::vec3* b); 
		static glm::vec2 tripleCrossProduct(glm::vec2 a, glm::vec2 b, glm::vec2 c);
		static float leastPenetrationAxis(const float* a_vertices, const float* b_vertices, int a_size, int b_size);
		static glm::vec2 calcMidpoint(float x1, float y1, float x2, float y2);
		static glm::vec2 calcFaceNormal(float x1, float y1, float x2, float y2);
		static float calcCircleInertia(float mass,float radius); 
		static float calcPolygonInertia(float density, const float* vertices, int size);
		static float minPointToLineDistance(float p1, float p2, float x1, float y1, float x2, float y2);

};