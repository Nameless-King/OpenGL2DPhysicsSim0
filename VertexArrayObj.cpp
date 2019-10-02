#include "VertexArrayObj.h"

#include <iostream>

VertexArrayObj::VertexArrayObj():m_attribCount(0){
	glGenVertexArrays(1,&m_ID);
	
}

VertexArrayObj::~VertexArrayObj(){
	
	glDeleteVertexArrays(1,&m_ID);
}

void VertexArrayObj::addFloatBuffer(const VertexBufferObj *vbo){
	
	bind();
	vbo->bind();
	
	for(int i = 0;i<8;i++){
	}
	
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

void VertexArrayObj::bind() const{
	glBindVertexArray(m_ID);
}

void VertexArrayObj::unbind() const{
	glBindVertexArray(0);
}