#include "VertexBufferObj.h"
#include <iostream>

VertexBufferObj::VertexBufferObj(const void *data, size_t byteSize, GLenum dataType, GLenum type, GLenum usage,unsigned int size, GLenum normalize):
	m_data(data), m_byteSize(byteSize), m_type(type),
	m_usage(usage), m_size(size), 
	m_normalize(normalize), m_dataType(dataType){
		glGenBuffers(1,&m_ID);
		
		glBindBuffer(m_type,m_ID);
		
		glBufferData(m_type,m_byteSize,m_data,m_usage);
		
	}
	
void VertexBufferObj::bind() const{
	glBindBuffer(m_type,m_ID);
}

void VertexBufferObj::unbind() const{
	glBindBuffer(m_type,0);
}

VertexBufferObj::~VertexBufferObj(){
	glDeleteBuffers(1,&m_ID);
}

