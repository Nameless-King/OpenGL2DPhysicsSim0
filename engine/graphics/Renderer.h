#pragma once

#include <GL/glew.h>

#include <iostream>

#include "./VAO.h"
#include "./VBO.h"
#include "./IBO.h"

class Renderer{
private:
	static VAO* s_vao;
	static VBO* s_vbo0;
	static VBO* s_vbo1;
	static IBO* s_ibo0;
	
	static const float s_vertices[];
	static const float s_uvCoords[];
	static const unsigned int s_indices[];
public:
	static const float* getVertices(); // COMPLETE
	static const float* getUVCoords(); // COMPLETE
	static const unsigned int* getIndices(); // COMPLETE
	
	static void init(); // COMPLETE
	static void bind(); // COMPLETE
	static void renderObject(); // COMPLETE
	static void unbind(); // COMPLETE
	static void destroy(); // COMPLETE
};