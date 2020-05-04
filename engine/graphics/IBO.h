#pragma once

#include <GL/glew.h>

class IBO{
private:
	unsigned int m_id;
	unsigned int m_vertexCount;
	size_t m_byteSize;
	const void* m_data;
	
public:
	IBO(); // COMPLETE
	IBO(unsigned int vertexCount, const void* data, size_t byteSize); // COMPLETE
	~IBO(); // COMPLETE
	
	inline unsigned int getID() const {return m_id;} // COMPLETE
	inline unsigned int getVertexCount() const {return m_vertexCount;} // COMPLETE
	inline size_t getByteSize() const {return m_byteSize;} // COMPLETE
	inline const void* getData() const {return m_data;} // COMPLETE
	
	void bind() const; // COMPLETE
	void unbind() const; // COMPLETE
};