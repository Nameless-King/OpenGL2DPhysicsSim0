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


void input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);

int x_pos = 0;
int y_pos = 0;

int WIDTH = 800;
int HEIGHT = 600;

Window windowObj(WIDTH, HEIGHT,"Hello,World");
Object obj0;

int main(){
	
	
	
	
	if(windowObj.getWindow() == NULL){
		return EXIT_FAILURE;
	}
	windowObj.setFramebufferSizeCallback(framebuffer_size_callback);
	

	
	if(glewInit() != GLEW_OK){
		std::cout << "Error glewInit" <<std::endl;
		return EXIT_FAILURE	;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//(void)io;
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(windowObj.getWindow(),true);
	ImGui_ImplOpenGL3_Init("#version 130");
	
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f,0.55f,0.60f,1.00f);
	
	//enable default opengl parameters and funcs
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//separate classes for each scene with gui options
	//add classes to control panel gui obj 
	//	-main gui to switch between scenes
	
	//Kinds of sim scenes:
	//1-d kinematic
	//2-dkinematic
	
	Shader shader0("./shaders/shader0.vs","./shaders/shader0.fs");
	
	//shader0.setUniform1i("u_textureSampler",0);
	
	Texture texture0("./textures/block0.jpg");
	
	
	float data[] = {
		//large coords  uv coords    small coords
		-50.0f, -50.0f, 0.0f, 0.0f, -0.5f, -0.5f,
		50.0f, -50.0f, 1.0f, 0.0f, 0.5f, -0.5f,
		50.0f, 50.0f, 1.0f, 1.0f, 0.5f, 0.5f,
		-50.0f, 50.0f, 0.0f, 1.0f, -0.5f, 0.5f
	};
	float vertices_50[] = {
		-50.0f, -50.0f, 
		50.0f, -50.0f, 
		50.0f, 50.0f, 
		-50.0f, 50.0f
	};
	
	float uv_coords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f,1.0f
	};
	
	//TODO : Delete
	float vertices_05[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f
	};
	
	unsigned int vao, ibo;
	//unsigned int vbo1,vbo2;
	
	VertexArrayObj vao0;
	
	VertexBufferObj vbo0(vertices_50,sizeof(vertices_50),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	VertexBufferObj vbo1(uv_coords,sizeof(uv_coords),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	
	vao0.addFloatBuffer(&vbo0);
	
	vao0.addFloatBuffer(&vbo1);
	
	
	
	/*
	TODO : Delete
	
	Improper implementation
	vao0.addFloatBufferData(vertices_05,sizeof(uv_coords),GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	vao0.addFloatBufferData(uv_coords,sizeof(uv_coords),GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	*/
	
	
	/*
	
	TODO : Delete
	
	Code below is abstracted
	
	glGenBuffers(1,&vbo1);
	glBindBuffer(GL_ARRAY_BUFFER,vbo1);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_05),&vertices_05,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	
	glGenBuffers(1,&vbo2);
	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	glBufferData(GL_ARRAY_BUFFER,sizeof(uv_coords),&uv_coords,GL_STATIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	*/
	
	
	
		
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	
	IndexBufferObj ibo0(sizeof(indices)/sizeof(unsigned int),indices,sizeof(indices));

	vao0.addIndexBuffer(&ibo0);
	
	
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0,0.0,0.0));
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
	
	
	
	
	
	obj0 = Object(
		&vao0,
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	
	while(!windowObj.windowShouldClose()){
		glfwPollEvents();
		
		
		input(windowObj.getWindow());
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		if(show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		
		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Begin("Hello, World!");
			
			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window",&show_demo_window);
			ImGui::Checkbox("Another Window",&show_another_window);
			ImGui::SliderFloat("float",&f,0.0f,1.0f);
			ImGui::ColorEdit3("clear color",(float*)&clear_color);
			if(ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d",counter);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Application delta time %.3f",ImGui::GetIO().DeltaTime);
			ImGui::End();
		}
		
		if(show_another_window){
			ImGui::Begin("Another Window",&show_another_window);
			ImGui::Text("Hello from another window!");
			if(ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
		
		
		glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		
		//render
		shader0.use();//bind shader
		//set uniform shader variables
		
		shader0.setUniformMat4f("u_projection",windowObj.getProjectionMatrix());
		shader0.setUniformMat4f("u_view",view);
		shader0.setUniformMat4f("u_model",obj0.getModelMatrix());
		obj0.getVAO()->bind();//bind the vao
		ibo0.bind();
		texture0.bind();//bind the texture
		glDrawElements(GL_TRIANGLES,ibo0.getVertexCount(),GL_UNSIGNED_INT,0);
		
		obj0.getVAO()->unbind();
		ibo0.unbind();
		texture0.unbind();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		windowObj.swapBuffers();
	}
	
	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	
	//cleanup
	glDeleteBuffers(1,&ibo);
	
	glfwTerminate();
	
	return 0;
	
}
	
void input(GLFWwindow* window){
	
	glm::vec3 currentPos = obj0.getPos();
	
	if(glfwGetKey(window,GLFW_KEY_W)){
		currentPos.y += 1.0f;
	}else if(glfwGetKey(window,GLFW_KEY_S)){
		currentPos.y -= 1.0f;
	}
	
	if(glfwGetKey(window,GLFW_KEY_D)){
		currentPos.x += 1.0f;
	}else if(glfwGetKey(window,GLFW_KEY_A)){
		currentPos.x -= 1.0f;
	}
	obj0.setPos(currentPos.x,currentPos.y,currentPos.z);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	windowObj.resize(width,height);
}