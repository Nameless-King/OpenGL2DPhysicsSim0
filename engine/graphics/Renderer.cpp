#include "Renderer.h"

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

VAO* Renderer::s_vao;
VBO* Renderer::s_vbo0;
VBO* Renderer::s_vbo1;
IBO* Renderer::s_ibo0;

void Renderer::init(){
	s_vao = new VAO();
	
	s_vbo0 = new VBO(s_vertices,sizeof(s_vertices),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	s_vbo1 = new VBO(s_uvCoords, sizeof(s_uvCoords),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	
	s_vao->addFloatBuffer(s_vbo0);
	s_vao->addFloatBuffer(s_vbo1);
	
	s_ibo0 = new IBO(sizeof(s_indices)/sizeof(unsigned int), s_indices,sizeof(s_indices));
	
	s_vao->addIndexBuffer(s_ibo0);
}

const float* Renderer::getVertices(){
	return s_vertices;
}

const float* Renderer::getUVCoords(){
	return s_uvCoords;
}

const unsigned int* Renderer::getIndices(){
	return s_indices;
}

void Renderer::bind(){
	s_vao->bind();
	s_vao->getIndexBuffer()->bind();
}

void Renderer::renderObject(){
	glDrawElements(GL_TRIANGLES,s_vao->getIndexBuffer()->getVertexCount(),GL_UNSIGNED_INT,0);
}

void Renderer::unbind(){
	s_vao->unbind();
	s_vao->getIndexBuffer()->unbind();
}

void Renderer::destroy(){
	delete s_vao;
	delete s_vbo0;
	delete s_vbo1;
	delete s_ibo0;
}