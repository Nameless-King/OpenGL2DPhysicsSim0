#include "StaticRenderer.h"

const float StaticRenderer::s_vertices[] = {
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
	
const float StaticRenderer::s_uvCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f
};
	
const unsigned int StaticRenderer::s_indices[] = {
	0,1,2,
	2,3,0
};

const float StaticRenderer::s_point[] = {
	0.0f,0.0f
};

VertexArrayObj* StaticRenderer::s_vao;
VertexArrayObj* StaticRenderer::s_pointVAO;
VertexBufferObj* StaticRenderer::s_pvbo0;
VertexBufferObj* StaticRenderer::s_pvbo1;
VertexBufferObj* StaticRenderer::s_pPointVBO0;
IndexBufferObj* StaticRenderer::s_pibo;

void StaticRenderer::init(){
	
	s_vao = new VertexArrayObj();

	s_pvbo0 =  new VertexBufferObj(s_vertices,sizeof(s_vertices),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	s_pvbo1 =  new VertexBufferObj(s_uvCoords,sizeof(s_uvCoords),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	
	s_vao->addFloatBuffer(s_pvbo0);
	s_vao->addFloatBuffer(s_pvbo1);
	
	s_pibo = new  IndexBufferObj(sizeof(s_indices)/sizeof(unsigned int), s_indices,sizeof(s_indices));
	s_vao->addIndexBuffer(s_pibo);
	
	//For particle points
	s_pointVAO = new VertexArrayObj();
	s_pPointVBO0 = new VertexBufferObj(s_point,sizeof(s_point),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	s_pointVAO->addFloatBuffer(s_pPointVBO0);
	
}

const float* StaticRenderer::getVertices(){
	return s_vertices;
}

const float* StaticRenderer::getUVCoords(){
	return s_uvCoords;
}

const unsigned int* StaticRenderer::getIndices(){
	return s_indices;
}

void StaticRenderer::bind(){
	s_vao->bind();
	s_vao->getIndexBuffer()->bind();
}

void StaticRenderer::bindPoint(){
	s_pointVAO->bind();
}

void StaticRenderer::renderObject(){
	glDrawElements(GL_TRIANGLES,s_vao->getIndexBuffer()->getVertexCount(),GL_UNSIGNED_INT,0);
}

void StaticRenderer::renderPoint(){
	glDrawArrays(GL_POINTS,0,1);
}

void StaticRenderer::unbind(){
	s_vao->unbind();
	s_vao->getIndexBuffer()->unbind();
}

void StaticRenderer::unbindPoint(){
	s_pointVAO->unbind();
}

void StaticRenderer::destroy(){
	delete s_vao;
	delete s_pvbo0;
	delete s_pvbo1;
	delete s_pibo;
	delete s_pointVAO;
	delete s_pPointVBO0;
}

