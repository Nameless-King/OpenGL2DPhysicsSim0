#include "VertexArrayObj.h"

VertexArrayObj::VertexArrayObj(unsigned int vaoID, int vertexCount):m_ID(vaoID),m_vertexCount(vertexCount){
}

VertexArrayObj::~VertexArrayObj(){
	glDeleteVertexArrays(1,&m_ID);
}

void VertexArrayObj::bind() const{
	glBindVertexArray(m_ID);
}

void VertexArrayObj::unbind() const{
	glBindVertexArray(0);
}