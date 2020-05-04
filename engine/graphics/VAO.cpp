#include "./VAO.h"

VAO::VAO():m_attribCount(0),m_pibo(nullptr){
	glGenVertexArrays(1,&m_id);
	
}

VAO::~VAO(){
	
	glDeleteVertexArrays(1,&m_id);
}

void VAO::addFloatBuffer(const VBO *vbo){
	
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

void VAO::addIndexBuffer(const IBO *ibo){
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

void VAO::bind() const{
	glBindVertexArray(m_id);
}

void VAO::unbind() const{
	glBindVertexArray(0);
}