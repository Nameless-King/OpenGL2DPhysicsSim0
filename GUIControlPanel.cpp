#include "./GuiControlPanel.h"

static std::vector<Scene*> scenes;

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
	for(int i = 0;i<scenes.size();i++){
		listScene(scenes[i]);
	}
	ImGui::End();
}

void GUIControlPanel::registerScene(Scene* scene){
	scenes.push_back(scene);
}

void GUIControlPanel::finalize(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIControlPanel::listScene(Scene* scene){
	if(!scene){
		ImGui::Text("Nan");
	}
	ImGui::Text(scene->getSceneTitle().c_str());
}