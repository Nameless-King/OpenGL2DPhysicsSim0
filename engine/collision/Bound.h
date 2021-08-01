#pragma once

#include <cmath>

#include "../../Dependencies/glm/glm.hpp"
#include "../maths/EngineMath.h"

enum class BoundingType{
	NA = 0,
	AxisAligned = 1,
	Circle = 2,
	Oriented = 3,
	Polygon = 4
};

struct Face{
	Face():
		x1(NULL),
		y1(NULL),
		x2(NULL),
		y2(NULL)
	{}

	const float *x1, *y1, *x2, *y2;
};

class Bound{
private:
	BoundingType m_type;

	glm::vec2* m_halfExtents;
	glm::vec2* m_center;
	glm::vec2* m_scale;
	float* m_rotation;
	const float* m_vertices;

	glm::vec2 m_localX;
	glm::vec2 m_localY;
	float m_furthestDistance;
	int m_vertexCount;

	Face* m_faceArray;
	glm::vec4* m_faces;
	
	
public:
	Bound(); 
	Bound(glm::vec2* center, float* rotation, glm::vec2* scale, const float* pvertices, int vertexCount, BoundingType type); 
	Bound(const Bound& bound);
	~Bound(); 

	inline const float* getVertices() const {return m_vertices;}
	inline const float getRotation() const {return *m_rotation;}
	inline const float getFurthestDistance() const {return m_furthestDistance;}
	inline const BoundingType getBoundingType() const {return m_type;}
	inline const glm::vec2 getLocalX() const {return m_localX;}
	inline const glm::vec2 getLocalY() const {return m_localY;}
	inline const glm::vec2* getCenter() const {return m_center;}
	inline const glm::vec2* getHalfExtents() const {return m_halfExtents;}
	inline const glm::vec2* getScale() const {return m_scale;}
	inline const int getVertexCount() const {return m_vertexCount;}

	glm::vec2 getCopyCenterXY() const;
	glm::vec2 getCopyHalfExtentsXY() const; 
	
	void setHalfExtents(glm::vec2* halfExtents);

	glm::vec4 getFaceAt(int index);
	Face* getFaceInArray(int index);
	glm::vec2 getFaceNormalAt(int index);

private:
	void createFaceArray();
};