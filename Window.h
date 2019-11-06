#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

class Window{
private:
	int m_width;
	int m_height;
	float m_zoom;
	bool m_sizeChanged;
	const std::string m_title;
	GLFWwindow *m_window;
	glm::mat4 m_projection;
	
public:
	Window(int width, int height, const std::string &title);
	~Window();
	
	GLFWwindow* getWindow() const {return m_window;}
	int windowShouldClose();
	void swapBuffers();
	void setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int));
	void zoom(float zoom);
	int getWidth() const { return m_width;}
	int getHeight() const {return m_height;}
	void resize(int width, int height);
	void pollEvents();
	glm::mat4 getProjectionMatrix();
	
};