#include "./GuiControlPanel.h"

static std::vector<Scene*> s_scenes;
static int s_currentScene = -1;

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
	ImGui::RadioButton("Default",&s_currentScene,-1);
	for(int i = 0;i<s_scenes.size();i++){
		listScene(s_scenes[i],i);
	}
	ImGui::End();
}

void GUIControlPanel::registerScene(Scene* scene){
	s_scenes.push_back(scene);
}

void GUIControlPanel::finalize(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIControlPanel::listScene(Scene* scene,int sceneIndex){
	if(!scene){
		ImGui::RadioButton("Default",&s_currentScene,sceneIndex);
	}
	ImGui::RadioButton(scene->getSceneTitle().c_str(),&s_currentScene,sceneIndex);
}

void GUIControlPanel::updateCurrentScene(Window* window){
	if(s_currentScene>=0){
		s_scenes[s_currentScene]->update(window);
	}
	
}

void GUIControlPanel::renderCurrentSceneGUI(){
	if(s_currentScene>=0){
		s_scenes[s_currentScene]->renderGUI();
	}
	
}

void GUIControlPanel::renderCurrentScene(Window* window){
	if(s_currentScene>=0){
		s_scenes[s_currentScene]->render(window);
	}
}