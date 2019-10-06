#pragma once

#include <GL/glew.h>

class IndexBufferObj{
private:
	unsigned int m_ID;
	unsigned int m_vertexCount;
	size_t m_byteSize;
	const void *m_data;
	
public:
	IndexBufferObj(unsigned int vertexCount,const void *data,size_t byteSize);
	~IndexBufferObj();
	
	inline unsigned int getID() const{return m_ID;}
	inline unsigned int getVertexCount() const { return m_vertexCount;}
	size_t getByteSize() const {return m_byteSize;}
	inline const void* getData() const {return m_data;}
	
	void bind() const;
	void unbind() const;
};