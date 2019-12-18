#include "./SceneIntegrator.h"

SceneIntegrator::SceneIntegrator():
	m_title("SceneIntegrator"),
	m_force(50.0f),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL){
}

SceneIntegrator::SceneIntegrator(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneIntegrator"),
	m_force(50.0f),
	m_shader(shader),
	m_texture(texture){
		
		m_player = new Object(
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(1.0f,1.0f,1.0f)
		);
		
		m_player->addVertices(vertices);
		m_player->createHitbox(HitboxType::Circle);
		
		RigidBody2D* rbPlayer = new RigidBody2D(5.0f);
		rbPlayer->setDamping(1.0f);
		
		m_player->addRigidBody2D(rbPlayer);
}

SceneIntegrator::~SceneIntegrator(){
	delete m_player;
}

std::string SceneIntegrator::getSceneTitle() const {
	return m_title;
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
	Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);
}

void SceneIntegrator::renderGUI(){
	float damping = m_player->getRigidBody2D()->getDamping();
	float mass = m_player->getRigidBody2D()->getMass();
	ImGui::Begin(m_title.c_str());
	ImGui::SliderFloat("mass",&mass,1.0f,50.0f);
	ImGui::SliderFloat("force",&m_force,10.0f,150.0f);
	ImGui::SliderFloat("damping",&damping,0.0f,1.0f);
	m_player->getRigidBody2D()->setDamping(damping);
	m_player->getRigidBody2D()->setMass(mass);
	ImGui::End();
}

void SceneIntegrator::input(Window* window){
	glm::vec2 force(0.0f,0.0f);
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		force.y = m_force;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		force.y = -m_force;
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		force.x = m_force;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		force.x = -m_force;
	}
	

	
	m_player->getRigidBody2D()->setForce(force.x,force.y);
	
	
}
