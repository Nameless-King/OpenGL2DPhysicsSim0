#include "Window.h"

Window::Window(int width, int height, const std::string& title): 
	m_width(width), 
	m_height(height), 
	 m_sizeChanged(false),
	 m_title(title),
	 m_clearColor(glm::vec4(1.0f,1.0f,1.0f,1.0f)),
	 m_cc(CameraController(glm::vec2(0.0f,0.0f))),
	 m_zoom(2.0f){
	
	if(!glfwInit()){
		std::cout << "Error glfwInit" << std::endl;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
	
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

void Window::closeWindow(){
	glfwSetWindowShouldClose(m_window,true);
}

void Window::swapBuffers(){
	glfwSwapBuffers(m_window);
}

void Window::setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int)){
	glfwSetFramebufferSizeCallback(m_window,callback);
}

glm::mat4 Window::getProjectionMatrix(){
	if(m_sizeChanged || m_zoom != m_cc.getCameraZoom()){
		m_projection = glm::ortho(
			-(m_width/m_cc.getCameraZoom()),
			(m_width/m_cc.getCameraZoom()),
			-(m_height/m_cc.getCameraZoom()),
			(m_height/m_cc.getCameraZoom()),
			-1.0f,
			1.0f
		);
		m_sizeChanged = false;
		m_zoom = m_cc.getCameraZoom();
	}
	return m_projection;
}

void Window::zoom(float zoom){
	m_zoom = zoom;
	m_sizeChanged = true;
}

void Window::resize(int width,int height){
	m_width = width;
	m_height = height;
	m_sizeChanged = true;
}

void Window::pollEvents(){
	glfwPollEvents();
}

void Window::displayWindowStats(){
	ImGui::Begin("Stats");
	int zoom = (int)m_cc.getCameraZoom();
	if(ImGui::SliderInt("Zoom",&zoom,2,12)){
		m_cc.setCameraZoom(zoom);
		m_sizeChanged = true;
	}
	ImGui::Text("Application Domain [%.3f,%.3f]",
		-(m_width/(m_cc.getCameraZoom())),
		(m_width/(m_cc.getCameraZoom())));
	ImGui::Text("Applicaiton Range 	[%.3f,%.3f]",
		-(m_height/(m_cc.getCameraZoom())),
		(m_height/(m_cc.getCameraZoom())));
	ImGui::ColorEdit3("clear color",(float*)&m_clearColor);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Application delta time (dt) %.3f",ImGui::GetIO().DeltaTime);
	ImGui::End();
}

void Window::clear(){
	glClearColor(m_clearColor.x,m_clearColor.y,m_clearColor.z,m_clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void Window::setClearColor(glm::vec4 clearColor){
	m_clearColor = glm::vec4(clearColor);
}

CameraController* Window::getCameraController(){
	return &m_cc;
}

void Window::sizeChanged(bool hasChanged){
	m_sizeChanged = hasChanged;
}