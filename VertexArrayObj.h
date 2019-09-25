#include <GL/glew.h>
#include <vector>

class VertexArrayObj{
private:
	unsigned int m_attribCount;
	unsigned int m_ID;

	std::vector<unsigned int> m_bufferIDs;
	
	
public:
	VertexArrayObj();
	~VertexArrayObj();
	
	inline unsigned int getID() const {return m_ID;}
	
	void addFloatBufferData(float data[], size_t byteSize, GLenum type, GLenum usage, int size, GLenum normalize);
	
	void bind() const;
	void unbind() const;
};