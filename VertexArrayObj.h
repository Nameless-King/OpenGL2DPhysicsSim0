#pragma once

#include <GL/glew.h>

#include "VertexBufferObj.h"
#include "IndexBufferObj.h"

class VertexArrayObj{
private:
	unsigned int m_attribCount;
	unsigned int m_ID;
	const IndexBufferObj* m_pibo;

public:
	VertexArrayObj();
	~VertexArrayObj();
	
	inline unsigned int getID() const {return m_ID;}
	inline const IndexBufferObj* getIndexBuffer() const {return m_pibo;}
	
	void addFloatBuffer(const VertexBufferObj *vbo);
	void addIndexBuffer(const IndexBufferObj *ibo);
	
	void bind() const;
	void unbind() const;
};