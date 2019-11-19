#pragma once

#include <GL/glew.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
	unsigned int m_ID;
	
	Shader (const char* vertexPath, const char* fragmentPath);
	~Shader();
	
	void use();
	
	void setUniformBool(const std::string& name, bool value) const;
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const;

private:
	const char* readShaderFile(const char* path);
	unsigned int compileShaderCode(const char* sourceCode, GLenum shaderType);
	
		
};