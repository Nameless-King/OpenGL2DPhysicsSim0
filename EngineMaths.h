#pragma once

#include <iostream>
#include <cmath>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class EngineMaths{
	public:
		static glm::vec2 componentProduct(glm::vec2* a, glm::vec2* b);
		static glm::vec3 componentProduct(glm::vec3* a, glm::vec3* b);
		static float theta(glm::vec2* a,glm::vec2* b);
		static float theta(glm::vec3* a,glm::vec3* b);
};