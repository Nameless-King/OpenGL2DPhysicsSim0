class IndexBufferObj{
private:
	unsigned int m_ID;
public:
	IndexBufferObj(unsigned int iboID);
	~IndexBufferObj();
	
	inline unsigned int getID() const{return m_ID;}
	
	void bind() const;
	void unbind() const;
};