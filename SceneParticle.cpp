#include "./SceneParticle.h"

SceneParticle::SceneParticle()
	:m_title("SceneParticle")
	,m_shader(NULL)
	,m_renderAmount(1){}
	
SceneParticle::SceneParticle(Shader* shader)
	:m_title("SceneParticle")
	,m_shader(shader)
	,m_renderAmount(1){
		
	int iMax = 200;
	int jMax = 200;

	for(int i = 0;i<iMax;i++){
		for(int j = 0;j<jMax;j++){
			m_particles.push_back(new Particle(glm::vec2(2.0f*i,2.0f*j)));
			RigidBody2D* rb = new RigidBody2D(5.0f);
			rb->setDamping(1.0f);
			m_particles[i*jMax+j]->addRigidBody2D(rb);
		}
	}
	
	for(int i2 = iMax,i = 0;i2<iMax*2;i2++,i++){
		for(int j = 0;j<jMax;j++){
			m_particles.push_back(new Particle(glm::vec2(-2.0f*i,2.0f*j)));
			RigidBody2D* rb = new RigidBody2D(5.0f);
			rb->setDamping(1.0f);
			m_particles[i2*jMax+j]->addRigidBody2D(rb);
		}
	}
}
	
SceneParticle::~SceneParticle(){

	for(int i = 0;i<m_particles.size();i++){
		delete m_particles[i];
	}
}

std::string SceneParticle::getSceneTitle() const{
	return m_title;
}

void SceneParticle::render(Window* window){
	StaticRenderer::bindPoint();
	
	m_shader->use();
	
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));
	

	for(int i = 0;i<m_renderAmount;i++){
		m_shader->setUniformMat4f("u_model",m_particles[i]->getModelMatrix());
		StaticRenderer::renderPoint();
	}
	
	StaticRenderer::unbindPoint();
}

void SceneParticle::update(Window* window){
}

void SceneParticle::renderGUI(){
	int amount = m_renderAmount;
	ImGui::Begin(m_title.c_str());
	if(ImGui::SliderInt("Particle Amount",&amount,1,m_particles.size())){
		m_renderAmount = amount;
	}
	ImGui::End();
}