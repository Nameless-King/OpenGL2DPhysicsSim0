#include "VertexArrayObj.h"

#include <iostream>

VertexArrayObj::VertexArrayObj():m_attribCount(0),m_pibo(nullptr){
	glGenVertexArrays(1,&m_ID);
	
}

VertexArrayObj::~VertexArrayObj(){
	
	glDeleteVertexArrays(1,&m_ID);
}

void VertexArrayObj::addFloatBuffer(const VertexBufferObj *vbo){
	
	bind();
	vbo->bind();
	
	
	
	glEnableVertexAttribArray(m_attribCount);
	
	glVertexAttribPointer(m_attribCount,
		vbo->getSize(),
		vbo->getDataType(),
		vbo->getNormalize(),
		sizeof(float)*vbo->getSize(),
		(void*)0);
	
	
	//Controls current index to place new attrib
	m_attribCount+=1;
	
	
	
	vbo->unbind();
	unbind();
	
	
}

void VertexArrayObj::addIndexBuffer(const IndexBufferObj *ibo){
	bind();
	ibo->bind();
	
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		ibo->getByteSize(),
		ibo->getData(),
		GL_STATIC_DRAW
	);
	
	ibo->unbind();
	unbind();
	
	m_pibo = ibo;
}

void VertexArrayObj::bind() const{
	glBindVertexArray(m_ID);
}

void VertexArrayObj::unbind() const{
	glBindVertexArray(0);
}