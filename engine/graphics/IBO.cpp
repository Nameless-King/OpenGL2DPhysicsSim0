#include "./IBO.h"


IBO::IBO():m_id(0), m_vertexCount(0),m_data(nullptr),m_byteSize(0){}

IBO::IBO(unsigned vertexCount,const void *data,size_t byteSize)
	:m_vertexCount(vertexCount),
	m_data(data),
	m_byteSize(byteSize){
	glGenBuffers(1,&m_id);
}

IBO::~IBO(){
	glDeleteBuffers(1,&m_id);
}

void IBO::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);
}

void IBO::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}