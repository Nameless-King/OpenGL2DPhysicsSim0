#include "./Bound.h"

Bound::Bound():
	m_type(BoundingType::NA),
	m_halfExtents(NULL),
	m_center(NULL),
	m_scale(NULL),
	m_rotation(nullptr),
	m_localX(glm::vec2(1.0f,0.0f)),
	m_localY(glm::vec2(0.0f,1.0f)),
	m_furthestDistance(-1),
	m_vertices(NULL),
	m_faces(NULL),
	m_faceArray(NULL),
	m_vertexCount(0)
{}

Bound::Bound(glm::vec2* center, float* rotation, glm::vec2* scale, const float* pvertices, int vertexCount, BoundingType type):
	m_type(type),
	m_center(center),
	m_scale(scale),
	m_halfExtents(EngineMath::calcHalfExtents(pvertices,scale)),
	m_rotation(rotation),
	m_localX(glm::vec2(1.0f,0.0f)),
	m_localY(glm::vec2(0.0f,1.0f)),
	m_furthestDistance(glm::length(*(m_halfExtents))),
	m_vertices(pvertices),
	m_faces(new glm::vec4[vertexCount]),
	m_faceArray(new Face[vertexCount]),
	m_vertexCount(vertexCount)
{
	createFaceArray();
}

Bound::Bound(const Bound& bound):
	m_type(bound.m_type),
	m_halfExtents(new glm::vec2(*bound.m_halfExtents)),
	m_center(bound.m_center),
	m_scale(bound.m_scale),
	m_rotation(bound.m_rotation),
	m_localX(glm::vec2(bound.m_localX)),
	m_localY(glm::vec2(bound.m_localY)),
	m_furthestDistance(bound.m_furthestDistance),
	m_vertices(bound.m_vertices),
	m_faces(bound.m_faces),
	m_faceArray(bound.m_faceArray),
	m_vertexCount(bound.m_vertexCount)
{}

Bound::~Bound(){
	delete m_halfExtents;
	delete[] m_faces;
	delete[] m_faceArray;
}

glm::vec2 Bound::getCopyCenterXY() const {
	return glm::vec2(
		m_center->x,
		m_center->y
	);
}


glm::vec2 Bound::getCopyHalfExtentsXY() const {
	return glm::vec2(
		m_halfExtents->x,
		m_halfExtents->y
	);
}

void Bound::setHalfExtents(glm::vec2* halfExtents)  {
	delete m_halfExtents;
	m_halfExtents = halfExtents;
}

glm::vec4 Bound::getFaceAt(int index){
	return glm::vec4(*(m_faces+index));
}
Face* Bound::getFaceInArray(int index){
	return m_faceArray + index;
}

glm::vec2 Bound::getFaceNormalAt(int index){
	if(index > m_vertexCount){
		std::cout << "Tried to access face normal at non-existent face: " << index << std::endl;
		return glm::vec2(0.0f,0.0f);
	}else{
		return EngineMath::calcFaceNormal(0.0f,0.0f,1.0f,1.0f);
	}
}

void Bound::createFaceArray(){
	float x,y,z,w;
	for(int i = 0;i<(m_vertexCount * 2) - 2;i+=2){
		x = *(m_vertices +i);
		y = *(m_vertices +i +1);

		z = *(m_vertices +i +2);
		w = *(m_vertices +i +3);

		*(m_faces + (i/2)) = glm::vec4(x,y,z,w);
	}
	x = *(m_vertices + (m_vertexCount * 2) - 2);
	y = *(m_vertices + (m_vertexCount * 2) - 1);
	z = *(m_vertices);
	w = *(m_vertices+1);
	*(m_faces + m_vertexCount - 1) = glm::vec4(x,y,z,w);



	for(int i = 0;i<(m_vertexCount * 2) - 2;i+=2){
		Face* currentFace = m_faceArray + (i/2);
		
		currentFace->x1 = m_vertices + i;
		currentFace->y1 = m_vertices + i + 1;
		currentFace->x2 = m_vertices + i + 2;
		currentFace->y2 = m_vertices + i + 3;
	}
	Face* lastFace = m_faceArray + m_vertexCount - 1;
	lastFace->x1 = m_vertices + (m_vertexCount * 2) - 2;
	lastFace->y1 = m_vertices + (m_vertexCount * 2) - 1;
	lastFace->x2 = m_vertices;
	lastFace->y2 = m_vertices + 1;

}