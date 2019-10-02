#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObj.h"
#include "VertexBufferObj.h"
#include "IndexBufferObj.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(){
	
	
	Window windowObj(800,600,"Hello, World!");
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
	
	float vertices_05[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f
	};
	
	unsigned int vao, ibo;
	//unsigned int vbo1,vbo2;
	
	VertexArrayObj vao0;
	
	VertexBufferObj vbo0(vertices_05,sizeof(vertices_05),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	VertexBufferObj vbo1(uv_coords,sizeof(uv_coords),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	
	vao0.addFloatBuffer(&vbo0);
	
	vao0.addFloatBuffer(&vbo1);
	
	/*
	Improper implementation
	vao0.addFloatBufferData(vertices_05,sizeof(uv_coords),GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	vao0.addFloatBufferData(uv_coords,sizeof(uv_coords),GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	*/
	
	
	/*
	
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
	
	
	//vbo1 = 0;
	//vbo2 = 0;
	
	//vao0.unbind();
	
		
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	
	
	
	//indices data
	vao0.bind();
	
	glGenBuffers(1,&ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),&indices,GL_STATIC_DRAW);
	
	vao0.unbind();
	
	IndexBufferObj ibo0(ibo,sizeof(indices)/sizeof(unsigned int));
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0,0.0,0.0));
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
	glm::mat4 projection = glm::ortho(-1.0f,1.0f,1.0f,-1.0f,-1.0f,1.0f);
	
	
	while(!windowObj.windowShouldClose()){
		glfwPollEvents();
		glClearColor(0.0f,1.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		
		//render
		shader0.use();//bind shader
		//set uniform shader variables
		shader0.setUniformMat4f("u_view",view);
		shader0.setUniformMat4f("u_projection",projection);
		shader0.setUniformMat4f("u_model",model);
		vao0.bind();//bind the vao
		ibo0.bind();
		texture0.bind();//bind the texture
		glDrawElements(GL_TRIANGLES,ibo0.getVertexCount(),GL_UNSIGNED_INT,0);
		
		vao0.unbind();
		ibo0.unbind();
		texture0.unbind();
		
		windowObj.swapBuffers();
	}
	
	//cleanup
	glDeleteBuffers(1,&ibo);
	
	glfwTerminate();
	
	return 0;
	
}
	
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}