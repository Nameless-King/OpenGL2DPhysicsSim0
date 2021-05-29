#pragma once

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <chrono>


#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"

#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"

#include "./GCamera.h"

class GWindow{
private:
	int m_width;
	int m_height;
	long long int m_startFrameTime;
	float m_zoom;
	bool m_sizeChanged;
	const std::string m_title;
	GLFWwindow* m_window;
	glm::mat4 m_projection;
	glm::vec4 m_clearColor;
	GCamera m_camera;
	
public:
	GWindow(int width, int height, const std::string& title); // COMPLETE
	~GWindow(); // COMPLETE
	
	inline const int getHeight() {return m_height;} // COMPLETE
	inline const int getWidth() {return m_width;} // COMPLETE
	inline GLFWwindow* getWindow() {return m_window;} // COMPLETE
	inline const float getZoom() {return m_zoom;} // COMPLETE
	inline const long long int getStartFrameTime() const {return m_startFrameTime;}
	
	GCamera* getCamera(); // COMPLETE
	glm::mat4 getProjectionMatrix(); // COMPLETE
	
	void setClearColor(glm::vec4 clearColor); // COMPLETE
	void setFramebufferSizeCallback(void(*callback)(GLFWwindow*,int,int)); // COMPLETE
	void setZoom(float zoom); // COMPLETE
	
	void setStartFrameTime(long long int time);
	void clear(); // COMPLETE
	int isRunning(); // COMPLETE
	void closeWindow(); // COMPLETE
	void swapBuffers(); // COMPLETE
	
	void resize(int width, int height); // COMPLETE

	void displayWindowStats(); // COMPLETE


	void sizeChanged(bool hasChanged); // COMPLETE
	void projectCoords(glm::vec2* coords); // COMPLETE
};

	