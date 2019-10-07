#pragma once

#include <Gl/glew.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "./VertexArrayObj.h"

class Renderer{
private:
	VertexArrayObj* m_pvao;
	
public:
	Renderer();
	Renderer(VertexArrayObj* pvao);
	~Renderer();

	void start();
	void renderObject(); 
	void end();
	
	
};