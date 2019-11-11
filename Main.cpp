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
#include "GUIControlPanel.h"
#include "AABB.h"
#include "Physics2D.h"

#include "SceneExample.h"
#include "SceneCRPC.h"
#include "SceneIntegrator.h"
#include "SceneForces.h"
#include "SceneParticle.h"
#include "SceneForceGenerator.h"
#include "SceneBuoyantForce.h"

void input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void updatePos(Object* obj);
void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam);

int WIDTH = 800;
int HEIGHT = 600;

Window windowObj(WIDTH, HEIGHT,"Hello,World");

int main(){
	
	if(windowObj.getWindow() == NULL){
		return EXIT_FAILURE;
	}
	windowObj.setFramebufferSizeCallback(framebuffer_size_callback);
	
	if(glewInit() != GLEW_OK){
		std::cout << "Error glewInit" <<std::endl;
		return EXIT_FAILURE	;
	}
	
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback,0);
	
	GUIControlPanel::init(windowObj.getWindow(),true);	

	ImVec4 clear_color = ImVec4(0.45f,0.55f,0.60f,1.00f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//separate classes for each scene with gui options
	//add classes to control panel gui obj 
	//	-main gui to switch between scenes
	
	//Kinds of sim scenes:
	//1-d kinematic
	//2-dkinematic
	
	Shader shader0("./shaders/shader0.vs","./shaders/shader0.fs");	
	Shader shaderPoint("./shaders/shaderPoint.vs","./shaders/shaderPoint.fs");
	
	Texture texture0("./textures/circle.png");
		
	StaticRenderer::init();
	
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
	
	SceneCRPC scene0(&shader0,&texture0,StaticRenderer::getVertices());
	SceneExample scene1(&shader0,&texture0,StaticRenderer::getVertices());
	SceneIntegrator scene2(&shader0,&texture0,StaticRenderer::getVertices());
	SceneForces scene3(&shader0, &texture0, StaticRenderer::getVertices());
	SceneParticle scene4(&shaderPoint);
	SceneForceGenerator scene5(&shader0, &texture0, StaticRenderer::getVertices());
	SceneBuoyantForce scene6(&shader0, &texture0 , StaticRenderer::getVertices());

	GUIControlPanel::registerScene(&scene1);
	GUIControlPanel::registerScene(&scene0);
	GUIControlPanel::registerScene(&scene2);
	GUIControlPanel::registerScene(&scene3);
	GUIControlPanel::registerScene(&scene4);
	GUIControlPanel::registerScene(&scene5);
	GUIControlPanel::registerScene(&scene6);

	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	
	bool yes = true;
	int zoom = 1.0f;
	while(!windowObj.windowShouldClose()){
		windowObj.pollEvents();
		input(windowObj.getWindow());
	
		GUIControlPanel::updateCurrentScene(&windowObj);
		GUIControlPanel::start();
		GUIControlPanel::renderMenu();
	
		ImGui::ShowDemoWindow(&yes);
		ImGui::Begin("Stats");
		if(ImGui::SliderInt("Zoom",&zoom,1,6)){
			windowObj.zoom(zoom/1.0f);
		}
		ImGui::Text("Application Domain [%.3f,%.3f]",
			-(windowObj.getWidth()/(2.0f*windowObj.getZoom())),
			(windowObj.getWidth()/(2.0f*windowObj.getZoom())));
		ImGui::Text("Applicaiton Range 	[%.3f,%.3f]",
			-(windowObj.getHeight()/(2.0f*windowObj.getZoom())),
			(windowObj.getHeight()/(2.0f*windowObj.getZoom())));
		ImGui::ColorEdit3("clear color",(float*)&clear_color);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Application delta time (dt) %.3f",ImGui::GetIO().DeltaTime);
		ImGui::End();
		
		GUIControlPanel::renderCurrentSceneGUI();
		
		glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);	

		GUIControlPanel::renderCurrentScene(&windowObj);
		GUIControlPanel::finalize();

		windowObj.swapBuffers();
	}
	
	StaticRenderer::destroy();
	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
		
	return 0;
	
}	

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0,width,height);
	windowObj.resize(width,height);
}

void input(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
		windowObj.closeWindow();
	}
}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam){
	
	 fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
	
}
