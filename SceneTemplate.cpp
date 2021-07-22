#include "./SceneRestingContact.h"

SceneTemplate::SceneTemplate():
	Scene("SceneTemplate"),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL){
}

SceneTemplate::SceneTemplate(Shader* shader, Texture* texture):
	Scene("SceneRestingContact"),
	m_shader(shader),
	m_texture(texture){
	
	m_player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		0.0f,
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	m_player->createBound(BoundingType::AxisAligned);
	m_player->addRigidbody2D(new Rigidbody2D(5.0f));

	addObject(m_player);
}

SceneRestingContact::~SceneRestingContact(){
}

void SceneRestingContact::render(GWindow* window){
	Renderer::bind();
    m_shader->use();
    m_texture->bind();
    m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
    m_shader->setUniformMat4f("u_view",window->getCamera()->getViewMatrix());

    ObjectRegistration* currentRegistry = m_firstObject;
    while(currentRegistry){
        m_shader->setUniformMat4f("u_model",currentRegistry->object->getModelMatrix());
        Renderer::renderObject();
        currentRegistry = currentRegistry->next;
    }
    m_texture->unbind();
    Renderer::unbind();
}

void SceneRestingContact::update(GWindow* window){
	startFrame();
	runPhysics(ImGui::GetIO().DeltaTime);
	
	input(window);
}

void SceneRestingContact::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneRestingContact::input(GWindow* window){
	
	
	if(GInput::isKeyDown(GLFW_KEY_UP)){
		
	}else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
		
	}
	
	if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
		
	}else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
		
	}
	
	
}


void SceneTest::runPhysics(float dt){

	goto forceSkip;

    //force generators
    ObjectRegistration* currentRegister = m_firstObject;
    while(currentRegister){
        currentRegister = currentRegister->next;
    }
    
	forceSkip:

    integrate(ImGui::GetIO().DeltaTime);
   
    generateContacts();
    //m_collisionResolver->resolveContacts(ImGui::GetIO().DeltaTime);
}