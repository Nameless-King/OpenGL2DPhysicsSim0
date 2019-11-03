#include "./SceneIntegrator.h"

SceneIntegrator::SceneIntegrator():
	m_title("SceneIntegrator"),
	m_active(false),
	m_accVal(50.05f),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL){
}

SceneIntegrator::SceneIntegrator(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneIntegrator"),
	m_active(false),
	m_accVal(50.0f),
	m_shader(shader),
	m_texture(texture){
		
		m_player = new Object(
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(1.0f,1.0f,1.0f)
		);
		
		m_player->addVertices(vertices);
		m_player->createAABB(BBType::Circle);
		
		RigidBody2D* rbPlayer = new RigidBody2D(5.0f);
		
		
		m_player->addRigidBody2D(rbPlayer);
}

SceneIntegrator::~SceneIntegrator(){
	delete m_player;
}

std::string SceneIntegrator::getSceneTitle() const {
	return m_title;
}

bool SceneIntegrator::isActive() const{
	return m_active;
}

void SceneIntegrator::render(Window* window){
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

void SceneIntegrator::update(Window* window){
	input(window);
	Physics2D::updatePos(m_player);
}

void SceneIntegrator::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::SliderFloat("acceleration",&m_accVal,10.0f,200.0f);
	ImGui::End();
}

void SceneIntegrator::setActive(bool active){
	m_active = active;
}

void SceneIntegrator::input(Window* window){
	glm::vec2 acceleration(0.0f,0.0f);
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		acceleration.y = m_accVal;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		acceleration.y = -m_accVal;
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		acceleration.x = m_accVal;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		acceleration.x = -m_accVal;
	}
	
	m_player->getRigidBody2D()->setAcceleration(acceleration.x,acceleration.y);
	
	
}