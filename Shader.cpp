#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::ifstream::failure e){
		std::cout << "error" << std::endl;
	}
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	unsigned int vertex, fragment;
	int success;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS,&success);
	if(success == GL_FALSE){
		int maxLength = 0;
		glGetShaderiv(vertex,GL_INFO_LOG_LENGTH,&maxLength);
		char* message = (char*)malloc(maxLength * sizeof(char));
		glGetShaderInfoLog(vertex,maxLength,&maxLength,message);
		std::cout << "ERROR SHADER VERTEX COMPILATION FAILED\n" << message << std::endl;
		free(message);
	}
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment,1,&fShaderCode,NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
	if(success == GL_FALSE){
		int maxLength = 0;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH,&maxLength);
		char* message = (char*)malloc(maxLength*sizeof(char));
		glGetShaderInfoLog(fragment,maxLength,&maxLength,message);
		std::cout << "ERROR SHADER FRAGMENT COMPILATION FAILED\n"<< message<<std::endl;
		free(message);
	}
	
	m_ID = glCreateProgram();
	glAttachShader(m_ID,vertex);
	glAttachShader(m_ID,fragment);
	glLinkProgram(m_ID);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
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