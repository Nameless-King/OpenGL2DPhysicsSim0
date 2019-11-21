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

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

class Physics2D{
public:
	static const float G;
	
	static glm::vec2 getGravity();
	static void updatePos(Object* obj);
	static void integrator2(Object* obj,float dt);
	static void integrator3(Object* obj,float dt);
	static void updatePos(Object* object, float dt);
	static void gravitate(glm::vec2 dir,float mag,Object* obj);
};

#endif
