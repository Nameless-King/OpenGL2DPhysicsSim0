#include "Renderer.h"

Renderer::Renderer():m_pvao(nullptr){}

Renderer::Renderer(VertexArrayObj* pvao):m_pvao(pvao){}

Renderer::~Renderer(){
}

void Renderer::start(){
	m_pvao->bind();
	m_pvao->getIndexBuffer()->bind();
}

void Renderer::renderObject(){
	glDrawElements(GL_TRIANGLES,m_pvao->getIndexBuffer()->getVertexCount(),GL_UNSIGNED_INT,0);
}

void Renderer::end(){
	m_pvao->unbind();
	m_pvao->getIndexBuffer()->unbind();
}