#ifndef PHYSICS2D_H_
#define PHYSICS2D_H_

#include <cmath>
#include <algorithm>
#include <iostream>
#include <assert.h>

#include "./Object.h"
#include "./AABB.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Physics2D{
public:
	static void resolveCollision(Object* a, Object* b, Collision collision);
	static void positionalCorrection(Object* a, Object* b,Collision collision);
};

#endif
