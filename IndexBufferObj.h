class IndexBufferObj{
private:
	unsigned int m_ID;
	unsigned int m_vertexCount;
public:
	IndexBufferObj(unsigned int iboID,unsigned int vertexCount);
	~IndexBufferObj();
	
	inline unsigned int getID() const{return m_ID;}
	inline unsigned int getVertexCount() const { return m_vertexCount;}
	
	void bind() const;
	void unbind() const;
};