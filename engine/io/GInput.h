#pragma once

#include <GLFW/glfw3.h>

#include "../../Dependencies/glm/glm.hpp"

class GInput{
private:
	static const int FIRST_KEY_CODE;
	
	static GLFWwindow* s_window;
	
	static bool s_keys[GLFW_KEY_LAST];
	static bool s_mouseButtons[GLFW_MOUSE_BUTTON_LAST];
	
	static float s_mouseWheelX;
	static float s_mouseWheelY;

public:
	static void setContext(GLFWwindow* window); // COMPLETE
	
	static bool isKeyDown(int key); // COMPLETE
	static bool isKeyPressed(int key); // COMPLETE
	static bool isKeyReleased(int key); // COMPLETE
	
	static bool isMouseButtonDown(int button); // COMPLETE
	static bool isMouseButtonPressed(int button); // COMPLETE
	static bool isMouseButtonReleased(int button); // COMPLETE
	
	static float getMouseX(); // COMPLETE
	static float getMouseY(); // COMPLETE
	static glm::vec2 getMouseXY(); // COMPLETE
	
	static float getWheelX(); // COMPLETE
	static float getWheelY(); // COMPLETE
	static glm::vec2 getWheelXY(); // COMPLETE
	
	static void update(); // COMPLETE
	
private:
	static void setWheelX(float offset); // COMPLETE
	static void setWheelY(float offset); // COMPLETE
	static void setWheelXY(float offsetx, float offsety); // COMPLETE
};
	