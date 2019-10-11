#include "IndexBufferObj.h"
#include <GL/glew.h>

IndexBufferObj::IndexBufferObj():m_vertexCount(0),m_data(nullptr),m_byteSize(0){}

IndexBufferObj::IndexBufferObj(unsigned vertexCount,const void *data,size_t byteSize)
	:m_vertexCount(vertexCount),
	m_data(data),
	m_byteSize(byteSize){
	glGenBuffers(1,&m_ID);
}

IndexBufferObj::~IndexBufferObj(){
	glDeleteBuffers(1,&m_ID);
}

void IndexBufferObj::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ID);
}

void IndexBufferObj::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}