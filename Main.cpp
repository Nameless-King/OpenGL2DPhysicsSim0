#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <string>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObj.h"
#include "VertexBufferObj.h"
#include "IndexBufferObj.h"
#include "Object.h"
#include "Renderer.h"
#include "StaticRenderer.h"
#include "SceneManager.h"
#include "Hitbox.h"
#include "Physics2D.h"

#include "SceneIntegrator.h"
#include "SceneForces.h"
#include "SceneParticle.h"
#include "SceneForceGenerator.h"
#include "SceneBuoyantForce.h"
#include "SceneCollisions.h"
#include "SceneRestingContact.h"
#include "ScenePhysicsSystem.h"
//#include "SceneMassAggregate.h"

void input();
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam);
void windowInput();

const int WIDTH = 800;
const int HEIGHT = 600;
int zoom = 1.0f;
bool shouldShowDemoWindow = true;

Window windowObj(WIDTH, HEIGHT,"Hello,World");

int main(){
	
	if(windowObj.getWindow() == NULL){
		return EXIT_FAILURE;
	}
	windowObj.setFramebufferSizeCallback(framebuffer_size_callback);
	windowObj.setClearColor(glm::vec4(0.9f,0.7f,0.7f,1.0f));

	if(glewInit() != GLEW_OK){
		std::cout << "Error glewInit" <<std::endl;
		return EXIT_FAILURE	;
	}
	
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback,0);
	
	SceneManager::init(windowObj.getWindow(),true);	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	Shader shaderQuad("./shaders/shaderQuad.vs","./shaders/shaderQuad.fs");	
	Shader shaderPoint("./shaders/shaderPoint.vs","./shaders/shaderPoint.fs");
	
	Texture textureCircle("./textures/circle.png");
	Texture textureRectangle("./textures/rectangle.png");
	Texture textureWhite("./textures/white.png");
		
	StaticRenderer::init();
	
	SceneIntegrator scene0(&shaderQuad,&textureCircle,StaticRenderer::getVertices());
	SceneForces scene1(&shaderQuad, &textureCircle, StaticRenderer::getVertices());
	SceneParticle scene2(&shaderPoint);
	SceneForceGenerator scene3(&shaderQuad, &textureCircle, StaticRenderer::getVertices());
	SceneBuoyantForce scene4(&shaderQuad, &textureCircle , StaticRenderer::getVertices());
	SceneCollisions scene5(&shaderQuad, &textureCircle, StaticRenderer::getVertices());
	SceneRestingContact scene6(&shaderQuad,&textureWhite,StaticRenderer::getVertices());
	ScenePhysicsSystem scene7(&shaderQuad, &textureWhite, StaticRenderer::getVertices());
	

	SceneManager::registerScene(&scene0);
	SceneManager::registerScene(&scene1);
	SceneManager::registerScene(&scene2);
	SceneManager::registerScene(&scene3);
	SceneManager::registerScene(&scene4);
	SceneManager::registerScene(&scene5);
	SceneManager::registerScene(&scene6);
	SceneManager::registerScene(&scene7);
	

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	while(!windowObj.windowShouldClose()){
		windowObj.pollEvents();
		input();
		windowInput();

		SceneManager::updateCurrentScene(&windowObj);
		SceneManager::start();
		SceneManager::renderMenu();
	
		windowObj.displayWindowStats();

		SceneManager::renderCurrentSceneGUI();
		
		windowObj.clear();

		SceneManager::renderCurrentScene(&windowObj);
		SceneManager::finalize();

		windowObj.swapBuffers();
	}
	
	StaticRenderer::destroy();
	std::cout << "Final Error Code: " << glGetError() << std::endl;
		
	return 0;
	
}	

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0,width,height);
	windowObj.resize(width,height);
}

void input(){
	if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_ESCAPE)){
		windowObj.closeWindow();
	}
}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam){
	
	 fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void windowInput(){
	float camSpeed = 2.0f;
	float zoomSpeed = 0.1f;

	glm::vec2 camPos = windowObj.getCameraController()->getCameraPos();

	float px = camPos.x;
	float py = camPos.y;
	float dz = windowObj.getCameraController()->getCameraZoom();

	if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_W)){
		py+=camSpeed;
	}else if (glfwGetKey(windowObj.getWindow(),GLFW_KEY_S)){
		py-=camSpeed;
	}

	if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_D)){
		px+=camSpeed;
	}else if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_A)){
		px-=camSpeed;
	}

	

	if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_E)){
		if(dz < 12.0f){
			dz += zoomSpeed;
		}
	}else if(glfwGetKey(windowObj.getWindow(),GLFW_KEY_Q)){
		if(dz > 2.0f){
			dz -= zoomSpeed;
		}
	}

	windowObj.getCameraController()->setCameraPos(px,py);
	//windowObj.zoom(dz);
	windowObj.getCameraController()->setCameraZoom(dz);
	
}
