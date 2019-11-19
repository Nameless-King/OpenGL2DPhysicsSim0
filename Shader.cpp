#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	const char* vertexShaderCode = readShaderFile(vertexPath);
	const char* fragmentShaderCode = readShaderFile(fragmentPath);
	
	unsigned int vertex, fragment;
	int success;
	
	vertex = compileShaderCode(vertexShaderCode,GL_VERTEX_SHADER);
	fragment = compileShaderCode(fragmentShaderCode,GL_FRAGMENT_SHADER);
	
	m_ID = glCreateProgram();
	glAttachShader(m_ID,vertex);
	glAttachShader(m_ID,fragment);
	glLinkProgram(m_ID);
	//shaders are no longer needed when attached to shader program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

const char* Shader::readShaderFile(const char* shaderPath){
	std::string shaderCode;
	std::ifstream fileReader;

	fileReader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try{
		fileReader.open(shaderPath);

		std::stringstream shaderStringStream;
		shaderStringStream << fileReader.rdbuf();
		
		fileReader.close();
		shaderCode = shaderStringStream.str();
	} catch (std::ifstream::failure e){
		std::cout << "Error with reading shader file: " << shaderPath << std::endl;
	}
	
	return shaderCode.c_str();
}

unsigned int Shader::compileShaderCode(const char* sourceCode, GLenum shaderType){
	int compileSuccess;
	unsigned int shaderId;
	
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &sourceCode, NULL);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS,&compileSuccess);
	if(compileSuccess == GL_FALSE){
		int maxLength = 0;
		glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&maxLength);
		char* message = (char*)malloc(maxLength * sizeof(char));
		glGetShaderInfoLog(shaderId,maxLength,&maxLength,message);
		std::cout << "ERROR SHADER COMPILATION FAILED\n" << message << std::endl;
		std::cout << "SHADER TYPE: " << shaderType << std::endl;
		free(message);
	}

	return shaderId;
}

Shader::~Shader(){
	glDeleteProgram(m_ID);
}

void Shader::use(){
	glUseProgram(m_ID);
}

void Shader::setUniformBool(const std::string &name, bool value) const{
	glUniform1i(glGetUniformLocation(m_ID,name.c_str()),(int)value);
}

void Shader::setUniform1i(const std::string &name, int value) const{ 
	glUniform1i(glGetUniformLocation(m_ID,name.c_str()),value);
}

void Shader::setUniform1f(const std::string &name, float value) const{
	glUniform1f(glGetUniformLocation(m_ID,name.c_str()),value);
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const {
	
	glUniformMatrix4fv(glGetUniformLocation(m_ID,name.c_str()),1,GL_FALSE, &matrix[0][0]);
	
}