#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

class Window{
private:
	int m_width;
	int m_height;
	const std::string m_title;
	GLFWwindow *m_window;
	
public:
	Window(int width, int height, const std::string &title);
	~Window();
	
	GLFWwindow* getWindow() const {return m_window;}
	int windowShouldClose();
	void swapBuffers();
	void setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int));
	int getWidth() const { return m_width;}
	int getHeight() const {return m_height;}
	
	
};