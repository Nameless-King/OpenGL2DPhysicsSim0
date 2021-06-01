#pragma once

#include "./OBB.h"
#include "./Bound.h"
#include "../Object.h"
#include <vector>
#include <algorithm>
#include <cmath>

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
	static float calculateClosingVelocity(CollisionData* col); // COMPLETE
	static float getSmallestComponent(glm::vec2* vec); //complete
	static CollisionData calculateCollision(Object* a, Object* b); // COMPLETE
	static void calculateAABBNormals(CollisionData* col);
	static bool isColliding(Bound* a, Bound* b); // COMPLETE
	static bool SATTest(OBB* a, OBB* b); // COMPLETE
	static bool correctObjects(CollisionData* data); //complete
	static void resolve(float dt, CollisionData* col); // COMPLETE
	static void resolveInterpenetration(float dt, CollisionData* col); // COMPLETE
	static void positionalCorrection(CollisionData* col);
	static float resolveRestingContactVelocity(float dt, CollisionData* col); // COMPLETE
	static float resolveVelocity(float dt, CollisionData* col); // COMPLETE
	static void resolveFriction(float dt, float impulse, CollisionData* col); // COMPLETE
	static bool GJKTest(Object* a, Object* b, std::vector<glm::vec2>* simplexVertices);
	static bool GJKTest2(Object* a, Object* b);

	static bool checkFlags(Object* a, Object* b);
	static bool boundingVolumeTest(Object* a, Object* b);



	static glm::vec2 getSupport(Object* object, glm::vec2 direction); // TODO
	static SimplexStatus updateSimplex(std::vector<glm::vec2>* simplexVertices, Object* a, Object* b, glm::vec2* direction); // TODO
	static bool addSupport(Object* a, Object* b, glm::vec2 direction, std::vector<glm::vec2>* simplexVertices);
	static Edge findClosestEdge(std::vector<glm::vec2> polytopeVertices, RotatingDirection rotDir);
	static glm::vec2 EPATest(std::vector<glm::vec2>& simplexVertices);

};