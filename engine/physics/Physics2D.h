#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>
#include <assert.h>

#include "../Object.h"
#include "../maths/EngineMath.h"

#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"

#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"

class Physics2D{
public:
	static const float G;
	
	static glm::vec2 getGravity(); // COMPLETE
	static void integrate(Object* obj,float dt); // COMPLETE
	static void gravitate(glm::vec2 dir,float mag, Object* obj); // COMPLETE
};