#include "./SceneExample.h"

SceneExample::SceneExample():
	m_title("SceneExample"),
	m_active(false),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL),
	m_speed(1.0f){
}

SceneExample::SceneExample(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneExample"),
	m_active(false),
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
	m_player->setAcceleration(1.0f);
	m_player->setRestitution(0);
	m_player->setMass(5.0f);
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
	m_player->setVelocity(0.0f,0.0f);
	
	input(window);
}

void SceneExample::setActive(bool active){
	m_active = active;
}

void SceneExample::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::SliderFloat("speed",&m_speed,0.01f,1000.0f);
	m_player->setAcceleration(m_speed);
	ImGui::End();
}

void SceneExample::input(Window* window){
	glm::vec3 currentPos = m_player->getPos();
	float dt = ImGui::GetIO().DeltaTime;
	
	float vel = m_player->getAcceleration()*dt;
	m_player->setVelocity(vel,vel);
	float pos = vel;
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		currentPos.y += pos;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		currentPos.y -= pos;
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		currentPos.x += pos;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		currentPos.x -= pos;
	}
	
	m_player->setPos(currentPos.x,currentPos.y,currentPos.z);
}

std::string SceneExample::getSceneTitle() const {
	return m_title;
}

bool SceneExample::isActive() const{
	return m_active;
}