#pragma once

#include <iostream>

#include "./VertexArrayObj.h"
#include "./Hitbox.h"
#include "./RigidBody2D.h"
#include "./OBB.h"
#include "./EngineMaths.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Object{
private:
	const float* m_vertices;
	OBB* m_obb;
	Hitbox m_hitbox;
	RigidBody2D* m_rigidbody;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	Object();
	Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Object();
	
	glm::mat4 getModelMatrix();

	void setPos(float xPos, float yPos, float zPos);
	void setPos(float xPos, float yPos);
	void setPos(glm::vec2 pos);
	void setRot(float xRot, float yRot, float zRot);
	void setScl(float xScl, float yScl, float zScl);
	
	void addRigidBody2D(RigidBody2D* rb);
	void addVertices(const float vertices[]);
	void createHitbox(HitboxType type);
	void addOBB();

	void setHalfExtents(float dx, float dy);

	void getPosXY(glm::vec2& pos);

	inline glm::vec3 getPositionXYZ() const {return m_position;}
	inline glm::vec3 getRotationXYZ() const {return m_rotation;}
	inline glm::vec3 getScaleXYZ() const {return m_scale;}

	inline glm::vec2 getPositionXY() const {return glm::vec2(m_position.x,m_position.y);}
	inline glm::vec2 getRotationXY() const {return glm::vec2(m_rotation.x,m_rotation.y);}
	inline glm::vec2 getScaleXY() const {return glm::vec2(m_scale.x,m_scale.y);}
	
	inline Hitbox getHitbox() const {return m_hitbox;}
	inline RigidBody2D* getRigidBody2D() const {return m_rigidbody;}
	inline OBB* getOBB()  {return m_obb;}
	
};

