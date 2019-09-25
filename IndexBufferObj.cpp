#include "IndexBufferObj.h"
#include <GL/glew.h>

IndexBufferObj::IndexBufferObj(unsigned int iboID,unsigned vertexCount):m_ID(iboID),m_vertexCount(vertexCount){
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