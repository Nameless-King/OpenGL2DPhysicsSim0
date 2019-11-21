#include "./SceneExample.h"

SceneExample::SceneExample():
	m_title("SceneExample"),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL),
	m_speed(1.0f){
}

SceneExample::SceneExample(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneExample"),
	m_speed(1.0f),
	m_shader(shader),
	m_texture(texture){
	
	m_player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	m_player->addVertices(vertices);
	m_player->createAABB(BBType::Circle);
	m_player->addRigidBody2D(new RigidBody2D(5.0f));
}

SceneExample::~SceneExample(){
	delete m_player;
}

void SceneExample::render(Window* window){
	StaticRenderer::bind();
	m_shader->use();
	m_texture->bind();
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f)));
	
	m_shader->setUniformMat4f("u_model",m_player->getModelMatrix());
	StaticRenderer::renderObject();
	
	m_texture->unbind();
	StaticRenderer::unbind();
}

void SceneExample::update(Window* window){

	
	input(window);
}

void SceneExample::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneExample::input(Window* window){
	
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		
	}
	
	
}

std::string SceneExample::getSceneTitle() const {
	return m_title;
}
