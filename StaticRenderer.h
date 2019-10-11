#pragma once

#include <GL/glew.h>

#include <iostream>

#include "./VertexArrayObj.h"
#include "./VertexBufferObj.h"
#include "./IndexBufferObj.h"


class StaticRenderer{
private:
	static VertexArrayObj* s_vao;
	static VertexBufferObj* s_pvbo0;
	static VertexBufferObj* s_pvbo1;
	static IndexBufferObj* s_pibo;
	static const float s_vertices[];
	static const float s_uvCoords[];
	static const unsigned int s_indices[];
	
public:
	static void init();
	static void bind();
	static void renderObject();
	static void unbind();
	static void destroy();
};