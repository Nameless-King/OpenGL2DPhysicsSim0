#include "VertexArrayObj.h"

VertexArrayObj::VertexArrayObj():m_attribCount(0){
	glGenVertexArrays(1,&m_ID);
	bind();
}

VertexArrayObj::~VertexArrayObj(){
	for(unsigned int id : m_bufferIDs){
		glDeleteBuffers(1,&id);
	}
	glDeleteVertexArrays(1,&m_ID);
}

void VertexArrayObj::addFloatBufferData(float data[],size_t byteSize,  GLenum type, GLenum usage, int size, GLenum normalize){
	unsigned int vbo_ID;
	
	
	
	glGenBuffers(1,&vbo_ID);
	glBindBuffer(type,vbo_ID);
	m_bufferIDs.push_back(vbo_ID);
	glBufferData(type,byteSize,&data,usage);
	glVertexAttribPointer(m_attribCount,size,GL_FLOAT,normalize,size*sizeof(float),(void*)0);
	glEnableVertexAttribArray(m_attribCount);
	
	glBindBuffer(type,0);
	
	
}

void VertexArrayObj::bind() const{
	glBindVertexArray(m_ID);
}

void VertexArrayObj::unbind() const{
	glBindVertexArray(0);
}