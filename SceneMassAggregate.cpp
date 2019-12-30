#include "./SceneMassAggregate.h"

SceneMassAggregate::SceneMassAggregate():
	m_title("SceneMassAggregate"){
}

SceneMassAggregate::SceneMassAggregate(unsigned int maxContacts, unsigned int iterations=0):
	m_title("SceneMassAggregate"){

}



SceneMassAggregate::~SceneMassAggregate(){
	
}

void SceneMassAggregate::render(Window* window){
	StaticRenderer::bind();
	m_shader->use();
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCameraController()->getViewMatrix());
	
	
	
	
	
	StaticRenderer::unbind();

}

void SceneMassAggregate::update(Window* window){
	startFrame();
	runPhysics(ImGui::GetIO().DeltaTime);
	
	input(window);
}

void SceneMassAggregate::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneMassAggregate::input(Window* window){
	
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_UP)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_DOWN)){
		
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_LEFT)){
		
	}
	
	
}

std::string SceneMassAggregate::getSceneTitle() const {
	return m_title;
}

void SceneMassAggregate::startFrame(){
	ParticleRegistration* currentRegister = m_firstParticle;
	while(currentRegister){
		//Remove all force from the accumulator
		currentRegister->particle->getRigidBody2D()->zeroForce();
		//get the next registration
		currentRegister = currentRegister->next;
	}
}

unsigned int SceneMassAggregate::generateContacts(){
	unsigned int limit = m_maxContacts;
	ParticleContact* nextContact = m_contacts;

	ContactGeneratorRegistration* currentRegister = m_firstContactGenerator;
	
	while(currentRegister){
		unsigned int used = currentRegister->generator->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;

		//when out of contacts
		if(limit <= 0){
			break;
		}

		currentRegister = currentRegister->next;
	}

	//return number of contacts used
	return m_maxContacts - limit;
}

void SceneMassAggregate::integrate(float dt){
	ParticleRegistration* currentRegister = m_firstParticle;
	while(currentRegister){
		//remove all forces from accumulator
		//Physics2D::integrate(reg->particle,dt);
		currentRegister = currentRegister->next;
	}
}


void SceneMassAggregate::runPhysics(float dt){
	//apply force generators

	integrate(ImGui::GetIO().DeltaTime);

	//generate contacts

	//process contacts
	//resolver.resolveContacts
}