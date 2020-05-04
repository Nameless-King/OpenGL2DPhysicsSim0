#pragma once

#include <GL/glew.h>

#include "VBO.h"
#include "IBO.h"

class VAO{
private:
	unsigned int m_attribCount;
	unsigned int m_id;
	const IBO* m_pibo;
	
public:
	VAO();
	~VAO();
	
	inline unsigned int getID() const {return m_id;}
	inline const IBO* getIndexBuffer() const { return m_pibo;}

	void addFloatBuffer(const VBO* vbo);
	void addIndexBuffer(const IBO* ibo);
	
	void bind() const;
	void unbind() const;
	
};