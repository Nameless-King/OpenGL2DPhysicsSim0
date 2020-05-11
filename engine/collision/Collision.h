#pragma once

#include "./OBB.h"
#include "./Bound.h"
#include "../Object.h"

struct CollisionData {
	CollisionData():
		restitution(0.0f),
		collisionNormal(glm::vec2(0.0f,0.0f)),
		penetrationDepth(glm::vec2(0.0f,0.0f)),
		distance(glm::vec2(0.0f,0.0f)){
			object[0] = NULL;
			object[1] = NULL;
	}

	CollisionData(const CollisionData& data):
		restitution(data.restitution),
		collisionNormal(glm::vec2(data.collisionNormal)),
		penetrationDepth(glm::vec2(data.penetrationDepth)),
		distance(glm::vec2(data.distance)){
		object[0] = data.object[0];
		object[1] = data.object[1];
	}

	Object* object[2];
	float restitution;
	glm::vec2 collisionNormal;
	glm::vec2 penetrationDepth;
	glm::vec2 distance;
};

class Collision{
	public:
		static float calculateClosingVelocity( CollisionData* col); // COMPLETE
		static float getSmallestComponent(glm::vec2* vec); //complete
		static CollisionData calculateCollision( Bound* a,  Bound* b); // COMPLETE
		static bool isColliding( Bound* a,  Bound* b); // COMPLETE
		static bool SATTest( OBB* a,  OBB* b); // COMPLETE
		static bool correctObjects(CollisionData* data); //complete
		static void resolve(float dt, CollisionData* col); // COMPLETE
		static void resolveInterpenetration(float dt, CollisionData* col); // COMPLETE
		static void positionalCorrection(CollisionData* col); 
		static void resolveRestingContactVelocity(float dt, CollisionData* col); // COMPLETE
		static float resolveVelocity(float dt, CollisionData* col); // COMPLETE
		static void resolveFriction(float dt, float impulse, CollisionData* col); // COMPLETE
		static void rotationImpulse(glm::vec2 impulse, CollisionData* col);
};