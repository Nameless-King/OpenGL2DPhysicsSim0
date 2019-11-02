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

void input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void updatePos(Object* obj);

int WIDTH = 800;
int HEIGHT = 600;

Window windowObj(WIDTH, HEIGHT,"Hello,World");

Object obj0, obj1, obj2;

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
	
	/*VertexArrayObj vao0;
	
	VertexBufferObj vbo0(vertices_50,sizeof(vertices_50),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	VertexBufferObj vbo1(uv_coords,sizeof(uv_coords),GL_FLOAT,GL_ARRAY_BUFFER,GL_STATIC_DRAW,2,GL_FALSE);
	vao0.addFloatBuffer(&vbo0);
	vao0.addFloatBuffer(&vbo1);
	
	
	
	IndexBufferObj ibo0(sizeof(indices)/sizeof(unsigned int),indices,sizeof(indices));
	vao0.addIndexBuffer(&ibo0);
	*/
	
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
	
	//Renderer renderer(&vao0);
	
	SceneCRPC scene0(&shader0,&texture0,vertices_50);
	
	obj0 = Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	obj1 = Object(
		glm::vec3(60.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);

	obj2 = Object(
		glm::vec3(0.0f,60.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);

	
	obj0.addVertices(vertices_50);
	obj0.createAABB(BBType::Circle);
	obj0.setAcceleration(1.0f);
	obj0.setRestitution(0);
	obj0.setMass(50.0f);
	
	obj1.addVertices(vertices_50);
	obj1.createAABB(BBType::Circle);
	obj1.setRestitution(0);
	obj1.setMass(5.0f);
	
	obj2.addVertices(vertices_50);
	obj2.createAABB(BBType::Circle);
	obj2.setRestitution(0);
	obj2.setMass(5.0f);

	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
	bool useGravity = false;
	static float speed = 1.0f;
	float gravity = 1.0f;
	
	
	
	while(!windowObj.windowShouldClose()){
		
		
		windowObj.pollEvents();
		
		scene0.update(&windowObj);
		/*
		obj0.setVelocity(0.0f,0.0f);
		obj1.setVelocity(0.0f,0.0f);
		obj2.setVelocity(0.0f,0.0f);	
		
		input(windowObj.getWindow());
		
		Collision obj01Col = AABB::getCollision(obj0.getBoundingBox(),obj1.getBoundingBox());
		Collision obj02Col = AABB::getCollision(obj0.getBoundingBox(),obj2.getBoundingBox());
		Collision obj12Col = AABB::getCollision(obj1.getBoundingBox(),obj2.getBoundingBox());

		if(obj01Col.colliding){
			Physics2D::resolveCollision(&obj0,&obj1,obj01Col);
			Physics2D::positionalCorrection(&obj0,&obj1,obj01Col);
		}
		
		if(obj02Col.colliding){
			Physics2D::resolveCollision(&obj0,&obj2,obj02Col);
			Physics2D::positionalCorrection(&obj0,&obj2,obj02Col);
		}

		if(obj12Col.colliding){
			Physics2D::resolveCollision(&obj1,&obj2,obj12Col);
			Physics2D::positionalCorrection(&obj1,&obj2,obj12Col);
		}
		
		//find out what these do (forgot)
		//updatePos(&obj0);
		//updatePos(&obj1);
		//updatePos(&obj2);
		
		
		
		
		if(useGravity){
			float newY = obj0.getPos().y - gravity;
			
			if(newY>-300.0f + obj0.getBoundingBox().getHalfExtents().y){
				obj0.setPos(obj0.getPos().x,newY,obj0.getPos().z);
			}else{
				obj0.setPos(obj0.getPos().x,-300.0f + obj0.getBoundingBox().getHalfExtents().y,obj0.getPos().z);
			}
			
			newY = obj1.getPos().y - gravity;
			
			if(newY>-300.0f + obj1.getBoundingBox().getHalfExtents().y){
				obj1.setPos(obj1.getPos().x,newY,obj1.getPos().z);
			}else{
				obj1.setPos(obj1.getPos().x,-300.0f + obj1.getBoundingBox().getHalfExtents().y,obj1.getPos().z);
			}
			
			newY = obj2.getPos().y - gravity;
			
			if(newY>-300.0f + obj2.getBoundingBox().getHalfExtents().y){
				obj2.setPos(obj2.getPos().x,newY,obj2.getPos().z);
			}else{
				obj2.setPos(obj2.getPos().x,-300.0f + obj2.getBoundingBox().getHalfExtents().y,obj2.getPos().z);
			}
		}
		*/
		
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
			//ImGui::SliderFloat("speed",&speed,0.1f,1000.0f);
			//if(ImGui::Button("Apply Speed"))
			//	obj0.setAcceleration(speed*100.0f);
			//ImGui::Checkbox("Use Gravity",&useGravity);
			//ImGui::SliderFloat("Gravity",&gravity,0.1f,1.0f);
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
		
		glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
		/*
		{
			StaticRenderer::bind();
			//renderer.start();
			
			shader0.use();
			
			texture0.bind();
			
			shader0.setUniformMat4f("u_projection",windowObj.getProjectionMatrix());
			shader0.setUniformMat4f("u_view",view);
			
			shader0.setUniformMat4f("u_model",obj0.getModelMatrix());
			
			StaticRenderer::renderObject();
			//renderer.renderObject();
			
			shader0.setUniformMat4f("u_model",obj1.getModelMatrix());
			
			StaticRenderer::renderObject();
			//renderer.renderObject();
			
			shader0.setUniformMat4f("u_model",obj2.getModelMatrix());

			StaticRenderer::renderObject();
			//renderer.renderObject();

			texture0.unbind();
			
			StaticRenderer::unbind();
			//renderer.end();
		}
		*/
		
		scene0.render(&windowObj);
		
		GUIControlPanel::finalize();
		
		windowObj.swapBuffers();
	}
	
	StaticRenderer::destroy();
	std::cout << "Retrieved Error Code: " << glGetError() << std::endl;
		
	return 0;
	
}
	
void input(GLFWwindow* window){
	
	if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
		glfwSetWindowShouldClose(window,true);
	}
	
	glm::vec3 currentPos = obj0.getPos();
	//get dt then calculate velocity and calculate position
	float dt = ImGui::GetIO().DeltaTime;
	float vel = obj0.getAcceleration() * dt;
	obj0.setVelocity(vel,vel);
	float pos = vel * dt;
	
	if(glfwGetKey(window,GLFW_KEY_W)){
		currentPos.y += pos;
	}else if(glfwGetKey(window,GLFW_KEY_S)){
		currentPos.y -= pos;
	}
	
	if(glfwGetKey(window,GLFW_KEY_D)){
		currentPos.x += pos;
	}else if(glfwGetKey(window,GLFW_KEY_A)){
		currentPos.x -= pos;
	}
	obj0.setPos(currentPos.x,currentPos.y,0.0f);
}

void updatePos(Object* obj){
	glm::vec2 resultingPosition = glm::vec2(obj->getPos().x,obj->getPos().y) + obj->getVelocity();
	obj->setPos(resultingPosition.x,resultingPosition.y,0.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	windowObj.resize(width,height);
}
