#include "./GuiControlPanel.h"

static std::vector<Scene*> scenes;
static int currentScene = -1;

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
	ImGui::RadioButton("NAN",&currentScene,-1);
	for(int i = 0;i<scenes.size();i++){
		listScene(scenes[i],i);
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

void GUIControlPanel::listScene(Scene* scene,int sceneIndex){
	if(!scene){
		ImGui::RadioButton("NAN",&currentScene,sceneIndex);
	}
	ImGui::RadioButton(scene->getSceneTitle().c_str(),&currentScene,sceneIndex);
}

void GUIControlPanel::updateCurrentScene(Window* window){
	if(currentScene!=-1){
		scenes[currentScene]->update(window);
	}
	
}

void GUIControlPanel::renderCurrentSceneGUI(){
	if(currentScene!=-1){
		scenes[currentScene]->renderGUI();
	}
	
}

void GUIControlPanel::renderCurrentScene(Window* window){
	if(currentScene!=-1){
		scenes[currentScene]->render(window);
	}
}