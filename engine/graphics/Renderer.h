#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./VAO.h"
#include "./VBO.h"
#include "./IBO.h"
#include "./Shader.h"


enum class BasicRenderMode{
	BRM_DISABLED = 0,
	BRM_DOT = 1,
	BRM_LINES = 2,
	BRM_LINE_LOOP = 3
};

class Renderer{
private:
	typedef struct {float r;float g;float b;float a;} Color;

	static VAO* s_vao;
	static VBO* s_vbo0;
	static VBO* s_vbo1;
	static IBO* s_ibo0;

	static const float s_vertices[];
	static const float s_uvCoords[];
	static const unsigned int s_indices[];

	static const int s_renderMode[];

	static BasicRenderMode s_BRMCurrentMode;
	static std::vector<float> s_BRMVertices;
	static std::vector<Shader*> s_BRMShaders;
	static unsigned int s_BRMVertexSplit;
	static Color s_BRMFragColor;
	static bool s_BRMCacheEnabled;

	static std::unordered_map<std::string,VAO*> s_BRMCache;

public:

	static const float* getVertices(); // COMPLETE
	static const float* getUVCoords(); // COMPLETE
	static const unsigned int* getIndices(); // COMPLETE
	
	static bool init(); // COMPLETE
	static void bind(); // COMPLETE
	static void renderObject(); // COMPLETE
	static void unbind(); // COMPLETE
	static void destroy(); // COMPLETE

	static void basicRenderBegin(BasicRenderMode mode);
	static void basicRenderEnd();
	static void basicRenderColor(float r, float g, float b, float a);
	static void basicRenderEnableCache();
	static void basicRenderPoint(float x, float y);
};