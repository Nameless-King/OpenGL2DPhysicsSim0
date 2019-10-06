#include "Window.h"

Window::Window(int width, int height, const std::string& title): m_width(width), m_height(height),  m_sizeChanged(false), m_title(title){
	
	if(!glfwInit()){
		std::cout << "Error glfwInit" << std::endl;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	
	m_window = glfwCreateWindow(m_width,m_height,m_title.c_str(),NULL,NULL);
	
	if(m_window == NULL){
		std::cout << "Error glfwCreateWindow" << std::endl;
	}
	
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	
	m_projection = glm::ortho(
		-(m_width/2.0f),
		(m_width/2.0f),
		-(m_height/2.0f),
		(m_height/2.0f),
		-1.0f,
		1.0f
	);
	
	
}

Window::~Window(){
	glfwTerminate();
}

int Window::windowShouldClose(){
	return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers(){
	glfwSwapBuffers(m_window);
}

void Window::setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int)){
	glfwSetFramebufferSizeCallback(m_window,callback);
}

glm::mat4 Window::getProjectionMatrix(){
	if(m_sizeChanged){
		m_projection = glm::ortho(
			-(m_width/2.0f),
			(m_width/2.0f),
			-(m_height/2.0f),
			(m_height/2.0f),
			-1.0f,
			1.0f
		);
		m_sizeChanged = false;
	}
	return m_projection;
}

void Window::resize(int width,int height){
	m_width = width;
	m_height = height;
	m_sizeChanged = true;
}
