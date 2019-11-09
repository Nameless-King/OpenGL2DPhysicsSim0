#include "./SceneParticle.h"

SceneParticle::SceneParticle()
	:m_title("SceneParticle")
	,m_shader(NULL)
	,m_particle(NULL)
	,m_active(false){}
	
SceneParticle::SceneParticle(Shader* shader)
	:m_title("SceneParticle")
	,m_shader(shader)
	,m_active(false){
		
	m_particle = new Particle(glm::vec2(0.0f,0.0f));
	RigidBody2D* rb = new RigidBody2D(5.0f);
	rb->setDamping(1.0f);
	m_particle->addRigidBody2D(rb);
	}
	
SceneParticle::~SceneParticle(){
	delete m_particle;
}

std::string SceneParticle::getSceneTitle() const{
	return m_title;
}

bool SceneParticle::isActive()const{
	return m_active;
}

void SceneParticle::render(Window* window){
	StaticRenderer::bindPoint();
	
	m_shader->use();
	
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));
	
	m_shader->setUniformMat4f("u_model",m_particle->getModelMatrix());
	
	StaticRenderer::renderPoint();
	
	StaticRenderer::unbindPoint();
}

void SceneParticle::update(Window* window){
}

void SceneParticle::setActive(bool active){
	m_active = active;
}

void SceneParticle::renderGUI(){
	ImGui::Begin(m_title.c_str());
	
	ImGui::End();
}