#include <GL/glew.h>

class VertexArrayObj{
private:
	unsigned int m_ID;
	int m_vertexCount;
	
public:
	VertexArrayObj(unsigned int vaoID, int vertexCount);
	~VertexArrayObj();
	
	inline unsigned int getID() const {return m_ID;}
	inline unsigned int getVertexCount() const {return m_vertexCount;}
	
	void bind() const;
	void unbind() const;
};