#include "IndexBufferObj.h"
#include <GL/glew.h>

IndexBufferObj::IndexBufferObj(unsigned int iboID):m_ID(iboID){
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