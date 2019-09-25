#include <GL/glew.h>

class VertexBufferObj{
private:
	unsigned int m_ID;
public:
	VertexBufferObj();
	~VertexBufferObj();
	
	inline unsigned int getID() const { return m_ID;}
};