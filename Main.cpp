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
#include "SceneCRPC.h"
#include "SceneExample.h"

void input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void updatePos(Object* obj);

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
	
	GUIControlPanel::init(windowObj.getWindow(),true);
		
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f,0.55f,0.60f,1.00f);
	
	//enable default opengl parameters and funcs
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
	Texture texture0("./textures/circle.png");
	
	float vertices_50[] = {
		-25.0f, -25.0f, 
		25.0f, -25.0f, 
		25.0f, 25.0f, 
		-25.0f, 25.0f
	};
	
	float uv_coords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f,1.0f
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	StaticRenderer::init();
	
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
	
	SceneCRPC scene0(&shader0,&texture0,vertices_50);
	SceneExample scene1(&shader0,&texture0,vertices_50);
	
	GUIControlPanel::registerScene(&scene0);
	GUIControlPanel::registerScene(&scene1);
	

	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	
	while(!windowObj.windowShouldClose()){
		
		
		windowObj.pollEvents();
		
		scene0.update(&windowObj);
		//scene1.update(&windowObj);
		
		GUIControlPanel::start();
		
		if(show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		
		{
			GUIControlPanel::renderMenu();
			static int counter = 0;
			
			ImGui::Begin("Hello, World!");
			
			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window",&show_demo_window);
			ImGui::Checkbox("Another Window",&show_another_window);
		
			ImGui::ColorEdit3("clear color",(float*)&clear_color);
			if(ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d",counter);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Application delta time (dt) %.3f",ImGui::GetIO().DeltaTime);
			ImGui::End();
		}
		
		if(show_another_window){
			ImGui::Begin("Another Window",&show_another_window);
			ImGui::Text("Hello from another window!");
			if(ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
		
		scene0.renderGUI();
		//scene1.renderGUI();
		
		glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
		scene0.render(&windowObj);
		//scene1.render(&windowObj);
		
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
	glViewport(0, 0, width, height);
	windowObj.resize(width,height);
}
