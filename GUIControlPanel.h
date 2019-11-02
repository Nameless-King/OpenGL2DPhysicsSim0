#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "./Scene.h"
#include "./Window.h"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

class GUIControlPanel{
public:
	static void init(GLFWwindow* window, bool installCallbacks);
	static void start();
	static void registerScene(Scene* scene);
	static void renderMenu();
	static void finalize();
	static void updateCurrentScene(Window* window);
	static void renderCurrentSceneGUI();
	static void renderCurrentScene(Window* window);
private:
	static void listScene(Scene* scene,int sceneIndex);
};