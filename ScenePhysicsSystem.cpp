#include "./ScenePhysicsSystem.h"

ScenePhysicsSystem::ScenePhysicsSystem():
	m_title("ScenePhysicsSystem"),
	m_shader(NULL),
	m_texture(NULL){
}

ScenePhysicsSystem::ScenePhysicsSystem(Shader* shader, Texture* texture, const float vertices[]):
	m_title("ScenePhysicsSystem"),
	m_shader(shader),
	m_texture(texture),
	m_maxContacts(0){

	m_firstObject = new ObjectRegistration();
	m_firstObject->object = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_firstObject->object->addVertices(vertices);
	m_firstObject->object->createHitbox(HitboxType::AxisAligned);
	m_firstObject->object->addRigidBody2D(new RigidBody2D(5.0f));

	m_collisionResolver = new CollisionBatchResolver(1);
}

ScenePhysicsSystem::~ScenePhysicsSystem(){
	ObjectRegistration* currentRegistry = m_firstObject;
	while(currentRegistry){
		delete currentRegistry->object;
		currentRegistry = currentRegistry->next;
	}

	delete m_collisionResolver;
}

void ScenePhysicsSystem::render(Window* window){
	StaticRenderer::bind();
	m_shader->use();
	m_texture->bind();
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCameraController()->getViewMatrix());
	
	ObjectRegistration* currentRegistry = m_firstObject;
	while(currentRegistry){
		m_shader->setUniformMat4f("u_model",currentRegistry->object->getModelMatrix());
		StaticRenderer::renderObject();

		currentRegistry = currentRegistry->next;
	}
	
	m_texture->unbind();
	StaticRenderer::unbind();
}

void ScenePhysicsSystem::update(Window* window){
	runPhysics(ImGui::GetIO().DeltaTime);
	
	input(window);
}

void ScenePhysicsSystem::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void ScenePhysicsSystem::input(Window* window){
	
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		
	}
	
	
}

std::string ScenePhysicsSystem::getSceneTitle() const {
	return m_title;
}

void ScenePhysicsSystem::startFrame(){
	ObjectRegistration* currentRegister = m_firstObject;

	while(currentRegister){
		//Remove all forces frome the accumulator
		currentRegister->object->getRigidBody2D()->zeroForce();
		//Get the next registration
		currentRegister = currentRegister->next;
	}
}

void ScenePhysicsSystem::generateContacts(){
	ObjectRegistration* hittee = m_firstObject;
	while(hittee){
		ObjectRegistration* hitter = hittee->next;
		while(hitter){
			ObjectContact generatedContact = ObjectContact::detectContact(hittee->object->getHitbox(),hitter->object->getHitbox());
			if(generatedContact.m_colliding){
				m_collisionResolver->registerContact(generatedContact);
			}
		}
		hittee = hittee->next;
	}
}

void ScenePhysicsSystem::integrate(float dt){
	ObjectRegistration* currentRegister = m_firstObject;
	while(currentRegister){
		Physics2D::integrator3(currentRegister->object,dt);
		currentRegister = currentRegister->next;
	}
}

void ScenePhysicsSystem::runPhysics(float dt){
	//apply force generators

	std::cout << "Integrating..." << std::endl;
	//integrate forces and update positions
	integrate(ImGui::GetIO().DeltaTime);

	std::cout << "Generating Contacts..." << std::endl;
	//generate contacts
	generateContacts();

	std::cout << "Resolving Contacts..." << std::endl;
	//process contacts
	m_collisionResolver->resolveContacts(ImGui::GetIO().DeltaTime);
}

