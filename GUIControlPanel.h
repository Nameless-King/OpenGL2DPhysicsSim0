#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "./Scene.h"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

class GUIControlPanel{
private:
	static void listScene(Scene* scene);
public:
	static void init(GLFWwindow* window, bool installCallbacks);
	static void start();
	static void renderMenu();
	static void finalize();
};