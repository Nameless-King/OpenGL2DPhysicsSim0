#include "GInput.h"

const int GInput::FIRST_KEY_CODE = 32;

GLFWwindow* GInput::s_window;

bool GInput::s_keys[GLFW_KEY_LAST];
bool GInput::s_mouseButtons[GLFW_MOUSE_BUTTON_LAST];

float GInput::s_mouseWheelX = 0;
float GInput::s_mouseWheelY = 0;

void GInput::setContext(GLFWwindow* win) {
	s_window = win;

	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		s_keys[i] = false;
	}

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		s_mouseButtons[i] = false;
	}
}

bool GInput::isKeyDown(int key) {
	return glfwGetKey(s_window, key);
}

bool GInput::isKeyPressed(int key) {
	return !s_keys[key] && isKeyDown(key);
}

bool GInput::isKeyReleased(int key) {
	return s_keys[key] && !isKeyDown(key);
}

bool GInput::isMouseButtonDown(int button) {
	return glfwGetMouseButton(s_window, button);
}

bool GInput::isMouseButtonPressed(int button) {
	return !s_mouseButtons[button] && isMouseButtonDown(button);
}

bool GInput::isMouseButtonReleased(int button) {
	return s_mouseButtons[button] && !isMouseButtonDown(button);
}

float GInput::getMouseX() {
	double mouseX = 0;
	glfwGetCursorPos(s_window, &mouseX, NULL);
	return (float)mouseX;
}

float GInput::getMouseY() {
	double mouseY = 0;
	glfwGetCursorPos(s_window, &mouseY, NULL);
	return (float)mouseY;
}

glm::vec2 GInput::getMouseXY() {
	double mouseX = 0;
	double mouseY = 0;
	glfwGetCursorPos(s_window, &mouseX, &mouseY);
	return glm::vec2((float)mouseX, (float)mouseY);
}

float GInput::getWheelX() {
	float current = s_mouseWheelX;
	setWheelX(0);
	return current;
}

float GInput::getWheelY() {
	float current = s_mouseWheelY;
	setWheelY(0);
	return current;
}

glm::vec2 GInput::getWheelXY() {
	float currentX = s_mouseWheelX;
	float currentY = s_mouseWheelY;

	setWheelXY(0, 0);

	return glm::vec2(currentX, currentY);
}

void GInput::update() {
	for (int i = FIRST_KEY_CODE; i < GLFW_KEY_LAST; i++) {
		s_keys[i] = isKeyDown(i);
	}

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		s_mouseButtons[i] = isMouseButtonDown(i);
	}
}

void GInput::setWheelX(float offset) {
	s_mouseWheelX = offset;
}

void GInput::setWheelY(float offset) {
	s_mouseWheelY = offset;
}

void GInput::setWheelXY(float offsetX, float offsetY) {
	s_mouseWheelX = offsetX;
	s_mouseWheelY = offsetY;
}