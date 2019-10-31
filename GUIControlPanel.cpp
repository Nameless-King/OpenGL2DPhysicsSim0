#include "./GuiControlPanel.h"

void GUIControlPanel::init(GLFWwindow* window, bool installCallbacks){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(window,installCallbacks);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void GUIControlPanel::start(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIControlPanel::renderMenu(){
	ImGui::Begin("Scene(s)");
	listScene(NULL);
	ImGui::End();
}

void GUIControlPanel::finalize(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIControlPanel::listScene(Scene* scene){
	
}