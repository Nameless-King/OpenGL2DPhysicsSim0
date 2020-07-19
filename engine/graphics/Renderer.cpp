#include "./Renderer.h"

const float Renderer::s_vertices[] = {
	/*-10.0f,-10.0f,
	10.0f,-10.0f,
	10.0f,10.0f,
	-10.0f,10.0f*/

	-5.0f,-5.0f,
	5.0f,-5.0f,
	5.0f,5.0f,
	-5.0f,5.0f

	/*-0.5f,-0.5f,
	0.5f,-0.5f,
	0.5f,0.5f,
	-0.5f,0.5f*/
};


const float Renderer::s_uvCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f
};

const unsigned int Renderer::s_indices[] = {
	0,1,2,
	2,3,0
};

const int Renderer::s_renderMode[] = {
	-1,
	GL_POINTS,
	GL_LINES,
	GL_LINE_LOOP
};

VAO* Renderer::s_vao;
VBO* Renderer::s_vbo0;
VBO* Renderer::s_vbo1;
IBO* Renderer::s_ibo0;


BasicRenderMode Renderer::s_BRMCurrentMode = BasicRenderMode::BRM_DISABLED;
unsigned int Renderer::s_BRMVertexSplit = 0;
Renderer::Color Renderer::s_BRMFragColor = { 1.0f,1.0f,1.0f,1.0f };
std::vector<float> Renderer::s_BRMVertices;
std::vector<Shader*> Renderer::s_BRMShaders;
std::unordered_map<std::string, VAO*> Renderer::s_BRMCache;
bool Renderer::s_BRMCacheEnabled = false;

void Renderer::init() {
	s_vao = new VAO();

	s_vbo0 = new VBO(s_vertices, sizeof(s_vertices), GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 2, GL_FALSE);
	s_vbo1 = new VBO(s_uvCoords, sizeof(s_uvCoords), GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 2, GL_FALSE);

	s_vao->addFloatBuffer(s_vbo0);
	s_vao->addFloatBuffer(s_vbo1);

	s_ibo0 = new IBO(sizeof(s_indices) / sizeof(unsigned int), s_indices, sizeof(s_indices));

	s_vao->addIndexBuffer(s_ibo0);


	s_BRMShaders.push_back(NULL);
	s_BRMShaders.push_back(new Shader("./shaders/shaderPoint.vs", "./shaders/shaderPoint.fs"));

}

const float* Renderer::getVertices() {
	return s_vertices;
}

const float* Renderer::getUVCoords() {
	return s_uvCoords;
}

const unsigned int* Renderer::getIndices() {
	return s_indices;
}

void Renderer::bind() {
	s_vao->bind();
	s_vao->getIndexBuffer()->bind();
}

void Renderer::renderObject() {
	glDrawElements(GL_TRIANGLES, s_vao->getIndexBuffer()->getVertexCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::unbind() {
	s_vao->unbind();
	s_vao->getIndexBuffer()->unbind();
}

void Renderer::basicRenderBegin(BasicRenderMode mode) {
	s_BRMCacheEnabled = false;
	s_BRMCurrentMode = mode;
	s_BRMVertexSplit = (int)mode;
	s_BRMVertices.clear();
}

void Renderer::basicRenderPoint(float x, float y) {
	s_BRMVertices.push_back(x);
	s_BRMVertices.push_back(y);
}

void Renderer::basicRenderColor(float r, float g, float b, float a) {
	s_BRMFragColor = { r,g,b,a };
}

void Renderer::basicRenderEnableCache() {
	s_BRMCacheEnabled = true;
}

void Renderer::basicRenderEnd() {

	Shader* currentShader = s_BRMShaders[1];
	//s_BRMVertexSplit = (int)s_BRMCurrentMode;

	unsigned int numVertices = s_BRMVertices.size() / 2;
	float* currentVertices = new float[numVertices * 2];
	for (int i = 0; i < numVertices * 2; i++) {
		*(currentVertices + i) = s_BRMVertices[i];
	}

	if (!numVertices)
		return;

	VAO* currentVAO;
	VAO tempVAO;

	if (s_BRMCacheEnabled) {
		std::string cacheID = s_BRMVertexSplit + "_" + numVertices;
		//TODO : look into try_emplace
		if (s_BRMCache.find(cacheID) == s_BRMCache.end()) {
			currentVAO = new VAO();

			VBO vertexBuffer = VBO(currentVertices, sizeof(currentVertices), GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 2, GL_FALSE);

			currentVAO->addFloatBuffer(&vertexBuffer);

			s_BRMCache.emplace(cacheID, currentVAO);

		}
		else {
			currentVAO = s_BRMCache.at(cacheID);
		}
	}
	else {
		VBO vertexBuffer = VBO(currentVertices, sizeof(float) * (numVertices * 2), GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 2, GL_FALSE);

		tempVAO.addFloatBuffer(&vertexBuffer);

		currentVAO = &tempVAO;
	}



	currentShader->use();

	currentVAO->bind();

	glDrawArrays(s_renderMode[(int)s_BRMCurrentMode], 0, numVertices);

	currentVAO->unbind();

}

void Renderer::destroy() {
	delete s_vao;
	delete s_vbo0;
	delete s_vbo1;
	delete s_ibo0;

	for (auto& x : s_BRMCache) {
		delete x.second;
	}

	for (int i = 0; i < s_BRMShaders.size(); i++) {
		delete s_BRMShaders[i];
	}
}