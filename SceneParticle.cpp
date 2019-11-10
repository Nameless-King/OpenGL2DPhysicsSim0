#include "./SceneParticle.h"

SceneParticle::SceneParticle()
	:m_title("SceneParticle")
	,m_shader(NULL)
	,m_active(false){}
	
SceneParticle::SceneParticle(Shader* shader)
	:m_title("SceneParticle")
	,m_shader(shader)
	,m_active(false){
		

	for(int i = 0;i<100;i++){
		for(int j = 0;j<20;j++){
			m_particles.push_back(new Particle(glm::vec2(5.0f*i,5.0f*j)));
			RigidBody2D* rb = new RigidBody2D(5.0f);
			rb->setDamping(1.0f);
			m_particles[i*10 + j]->addRigidBody2D(rb);
		}
	}
	
	}
	
SceneParticle::~SceneParticle(){

	for(int i = 0;i<m_particles.size();i++){
		//delete m_particles[i];
	}
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
	

	for(int i = 0;i<m_particles.size();i++){
		m_shader->setUniformMat4f("u_model",m_particles[i]->getModelMatrix());
		StaticRenderer::renderPoint();
	}
	
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