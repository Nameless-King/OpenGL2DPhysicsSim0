#include "./GWindow.h"

GWindow::GWindow(int width, int height, const std::string& title):
	m_width(width),
	m_height(height),
	m_sizeChanged(false),
	m_title(title),
	m_clearColor(glm::vec4(0.0f,1.0f,0.0f,1.0f)),
	m_camera(GCamera(glm::vec2(0.0f,0.0f))),
	m_zoom(1.0f){
		
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
		-(m_width/2.0f)/m_zoom,
		(m_width/2.0f)/m_zoom,
		-(m_height/2.0f)/m_zoom,
		(m_height/2.0f)/m_zoom,
		-1.0f,
		1.0f
	);
}

GWindow::~GWindow(){
	glfwTerminate();
}

GCamera* GWindow::getCamera(){
	return &m_camera;
}

glm::mat4 GWindow::getProjectionMatrix(){
	if(m_sizeChanged || m_zoom != m_camera.getCameraZoom()){
		m_sizeChanged = false;
		m_zoom = m_camera.getCameraZoom();
		m_projection = glm::ortho(
			-(m_width/2.0f)/m_zoom,
			(m_width/2.0f)/m_zoom,
			-(m_height/2.0f)/m_zoom,
			(m_height/2.0f)/m_zoom
		);
	}
	return m_projection;
}

void GWindow::setClearColor(glm::vec4 clearColor){
	m_clearColor = glm::vec4(clearColor);
}

void GWindow::setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int)){
	glfwSetFramebufferSizeCallback(m_window,callback);
}

void GWindow::setZoom(float zoom){
	m_zoom = zoom;
	m_sizeChanged = true;
}

void GWindow::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_clearColor.x,m_clearColor.y,m_clearColor.z,m_clearColor.w);
}

int GWindow::windowShouldClose(){
	return glfwWindowShouldClose(m_window);
}

void GWindow::closeWindow(){
	glfwSetWindowShouldClose(m_window,true);
}

void GWindow::swapBuffers(){
	glfwSwapBuffers(m_window);
}

void GWindow::resize(int width, int height){
	m_width = width;
	m_height = height;
	m_sizeChanged = true;
}

void GWindow::sizeChanged(bool hasChanged){
	m_sizeChanged = hasChanged;
}

void GWindow::pollEvents(){
	glfwPollEvents();
}

void GWindow::displayWindowStats(){
	ImGui::Begin("Stats");
	int zoom = (int)m_camera.getCameraZoom();
	if(ImGui::SliderInt("Zoom",&zoom,2,12)){
		m_camera.setCameraZoom(zoom);
		m_sizeChanged = true;
	}
	ImGui::Text("Application Domain [%.3f,%.3f]",
		-(m_width/(m_camera.getCameraZoom())),
		(m_width/(m_camera.getCameraZoom())));
	ImGui::Text("Applicaiton Range 	[%.3f,%.3f]",
		-(m_height/(m_camera.getCameraZoom())),
		(m_height/(m_camera.getCameraZoom())));
	double posX = 0;
	double posY = 0;
	glfwGetCursorPos(m_window,&posX,&posY);
	ImGui::Text("Mouse Position (user resizing may cause misinformation) [%.3f,%.3f]",posX - (m_width/2.0f), -posY + (m_height/2.0f));
	ImGui::ColorEdit3("clear color",(float*)&m_clearColor);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Application delta time (dt) %.3f",ImGui::GetIO().DeltaTime);
	ImGui::End();
}
