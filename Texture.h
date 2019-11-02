#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include "./Dependencies/stb_image.h"

class Texture{
private:
	std::string m_filepath;
	unsigned char* m_imagebuffer;
	int m_width, m_height, m_BPP;
	unsigned int m_ID;
public:
	Texture(const std::string& path);
	~Texture();
	
	void bind(unsigned int slot = 0) const;
	void unbind() const;
	
	inline int getWidth() const {return m_width;}
	inline int getHeight() const {return m_height;}
	inline unsigned int getID() const {return m_ID;}
	
};