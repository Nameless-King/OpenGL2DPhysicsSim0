#pragma once

#include "./OBB.h"
#include "./Bound.h"
#include "../Object.h"
#include <vector>
#include <algorithm>
#include <cmath>

struct CollisionData_NOTNULL{
	CollisionData_NOTNULL():
		hasCollided(false),
		restitution(0.0f),
		collisionNormal(glm::vec2(0.0f,0.0f)),
		penetrationDepth(0.0f),
		distance(glm::vec2(0.0f,0.0f)){
			rigidbody[0] = NULL;
			rigidbody[1] = NULL;
		}

	CollisionData_NOTNULL(const CollisionData_NOTNULL& data):
		hasCollided(data.hasCollided),
		restitution(data.restitution),
		collisionNormal(glm::vec2(data.collisionNormal)),
		penetrationDepth(data.penetrationDepth),
		distance(glm::vec2(data.distance)){
			rigidbody[0] = data.rigidbody[0];
			rigidbody[1] = data.rigidbody[1];
		}

		bool hasCollided;
		Rigidbody2D* rigidbody[2];
		float restitution;
		glm::vec2 collisionNormal;
		float penetrationDepth;
		glm::vec2 distance;
};

struct CollisionData {
	CollisionData() :
		restitution(0.0f),
		collisionNormal(glm::vec2(0.0f, 0.0f)),
		penetrationDepth(0.0f),
		distance(glm::vec2(0.0f, 0.0f)) {
		object[0] = NULL;
		object[1] = NULL;
	}

	CollisionData(const CollisionData& data) :
		restitution(data.restitution),
		collisionNormal(glm::vec2(data.collisionNormal)),
		penetrationDepth(data.penetrationDepth),
		distance(glm::vec2(data.distance)) {
		object[0] = data.object[0];
		object[1] = data.object[1];
	}

	Object* object[2];
	float restitution;
	glm::vec2 collisionNormal;
	//glm::vec2 penetrationDepth;
	float penetrationDepth;
	glm::vec2 distance;
};

struct Edge {
	float distance;
	glm::vec2 normal;
	int index;
};

enum class SimplexStatus {
	NotIntersecting ,
	AreIntersecting ,
	Searching 
};

enum class RotatingDirection {
	Clockwise ,
	CounterClockwise
};


class Collision {
public:
	static CollisionData calculateCollision(Object* a, Object* b); // COMPLETE
	static float calculateClosingVelocity(CollisionData* col); // COMPLETE
	static float resolveVelocity(float dt, CollisionData* col); // COMPLETE
	static void resolveFriction(float dt, float impulse, CollisionData* col); // COMPLETE
	static void resolveInterpenetration(float dt, CollisionData* col); // COMPLETE
	
	static CollisionData_NOTNULL calculateCollision_NOTNULL(Object* a, Object* b);
	static glm::vec2 calculateAABBNormals_NOTNULL(Object* a, Object* ,glm::vec2 distance);
	static float calculateClosingVelocity_NOTNULL(CollisionData_NOTNULL* col);
	static float resolveVelocity_NOTNULL(float dt, CollisionData_NOTNULL* col);
	static void resolveFriction_NOTNULL(float dt, float impulse, CollisionData_NOTNULL* col); 
	static void resolveInterpenetration_NOTNULL(float dt, CollisionData_NOTNULL* col);
	static void resolve_NOTNULL(float dt, CollisionData_NOTNULL* col);

	static float getSmallestComponent(glm::vec2* vec); //complete
	static void positionalCorrection(CollisionData* col);
	static void calculateAABBNormals(CollisionData* col);
	static bool isColliding(Bound* a, Bound* b); // COMPLETE
	static bool SATTest(OBB* a, OBB* b); // COMPLETE
	static bool correctObjects(CollisionData* data); //complete
	static void resolve(float dt, CollisionData* col); // COMPLETE
	static float resolveRestingContactVelocity(float dt, CollisionData* col); // COMPLETE
	static bool GJKTest(Object* a, Object* b, std::vector<glm::vec2>* simplexVertices);
	static bool GJKTest2(Object* a, Object* b);

	static bool checkFlags(Object* a, Object* b);
	static bool boundingVolumeTest(Object* a, Object* b);

	static CollisionData_NOTNULL collisionAABBvsAABB(Object* a, Object* b);
	static CollisionData_NOTNULL collisionCirclevsCircle(Object* a, Object* b);
	static CollisionData_NOTNULL collisionAABBvsCircle(Object* a, Object* b);
	static CollisionData_NOTNULL collisionOBBvsOBB(Object* a, Object* b);
	static CollisionData_NOTNULL collisionPolygonvsPolygon(Object* a, Object* b);
	static CollisionData_NOTNULL collisionPolygonvsCircle(Object* a, Object* b);

	static glm::vec2 getSupport(Object* object, glm::vec2 direction); // TODO
	static SimplexStatus updateSimplex(std::vector<glm::vec2>* simplexVertices, Object* a, Object* b, glm::vec2* direction); // TODO
	static bool addSupport(Object* a, Object* b, glm::vec2 direction, std::vector<glm::vec2>* simplexVertices);
	static Edge findClosestEdge(std::vector<glm::vec2> polytopeVertices, RotatingDirection rotDir);
	static glm::vec2 EPATest(std::vector<glm::vec2>& simplexVertices);
	static float calcFurthestSupport(Bound* a, Bound* b);

};