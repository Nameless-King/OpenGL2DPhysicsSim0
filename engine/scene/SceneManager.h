#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "./Scene.h"
#include "../io/GWindow.h"

#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_impl_glfw.h"
#include "../../Dependencies/imgui/imgui_impl_opengl3.h"

class SceneManager {
public:
	static void init(GLFWwindow* window, bool installCallbacks);
	static void start();
	static void registerScene(Scene* scene);
	static void renderMenu();
	static void finalize();
	static void updateCurrentScene(GWindow* window);
	static void renderCurrentSceneGUI();
	static void renderCurrentScene(GWindow* window);
	static void setCurrentScene(int sceneIndex);
	static void destroy();
private:
	static void listScene(Scene* scene, int sceneIndex);
};