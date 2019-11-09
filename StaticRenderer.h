#pragma once

#include <GL/glew.h>

#include <iostream>

#include "./VertexArrayObj.h"
#include "./VertexBufferObj.h"
#include "./IndexBufferObj.h"


class StaticRenderer{
private:
	static VertexArrayObj* s_vao;
	static VertexArrayObj* s_pointVAO;
	static VertexBufferObj* s_pvbo0;
	static VertexBufferObj* s_pvbo1;
	static VertexBufferObj* s_pPointVBO0;
	static IndexBufferObj* s_pibo;
	static const float s_vertices[];
	static const float s_uvCoords[];
	static const unsigned int s_indices[];
	static const float s_point[];
	
public:
	static const float* getVertices();
	static const float* getUVCoords();
	static const unsigned int* getIndices();
	static void init();
	static void bind();
	static void bindPoint();
	static void renderObject();
	static void renderPoint();
	static void unbind();
	static void unbindPoint();
	static void destroy();
};