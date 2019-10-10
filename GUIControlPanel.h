#pragma once

#include <GLFW/glfw3.h>

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

class GUIControlPanel{
public:
	static void init(GLFWwindow* window, bool installCallbacks);
	static void start();
	static void finalize();
};