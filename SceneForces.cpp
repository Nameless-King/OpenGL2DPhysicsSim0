#include "./SceneForces.h"

SceneForces::SceneForces():
	Scene("SceneForces"),
	m_force(50.0f),
	m_gravityMultiplier(1.0f),
	m_useGravity(false),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL){
}

SceneForces::SceneForces(Shader* shader, Texture* texture):
	Scene("SceneForces"),
	m_gravityMultiplier(1.0f),
	m_useGravity(false),
	m_force(50.0f),
	m_shader(shader),
	m_texture(texture){
	
	m_player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_player->createBound(BoundingType::AxisAligned);
	m_player->addRigidbody2D(new Rigidbody2D(5.0f));
	addObject(m_player);
	
}

SceneForces::~SceneForces(){
}


void SceneForces::render(GWindow* window){
	Renderer::bind();
	
	m_shader->use();
	m_texture->bind();
	
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCamera()->getViewMatrix());
	
	ObjectRegistration* currentRegistry = m_firstObject;
	while(currentRegistry){
		m_shader->setUniformMat4f("u_model", currentRegistry->object->getModelMatrix());
		Renderer::renderObject();
		currentRegistry = currentRegistry->next;
	}
	
	m_texture->unbind();
	Renderer::unbind();
}

void SceneForces::update(GWindow* window){
	startFrame();
	input(window);
	runPhysics(ImGui::GetIO().DeltaTime,window);
	
}

void SceneForces::renderGUI(){
	float mass = m_player->getRigidbody2D()->getMass();
	bool useGravity = m_useGravity;
	
	ImGui::Begin(m_title.c_str());
	ImGui::SliderFloat("force",&m_force,10.0f,150.0f);
	if(ImGui::SliderFloat("mass",&mass,1.0f,50.0f)){
		m_player->getRigidbody2D()->setMass(mass);
	}
	ImGui::SliderFloat("Gravity Multiplier",&m_gravityMultiplier,1.0f,20.0f);
	if(ImGui::Checkbox("Use Gravity",&useGravity)){
		m_useGravity = useGravity;
	}
	ImGui::End();
}

void SceneForces::input(GWindow* window){
	glm::vec2 force(0.0f,0.0f);
	
	if(GInput::isKeyDown(GLFW_KEY_UP)){
		force.y = m_force;
	}else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
		force.y = -m_force;
	}
	
	if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
		force.x = m_force;
	}else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
		force.x = -m_force;
	}
	
	m_player->getRigidbody2D()->addForce(force);

}

void SceneForces::runPhysics(float dt,GWindow* window){
	glm::vec2 mousePos = GInput::getMouseXY();
	window->projectCoords(&mousePos);

	ObjectRegistration* current = m_firstObject;
	while(current){
		if(m_useGravity){
			Physics2D::gravitate(mousePos,m_gravityMultiplier * m_force,current->object);
		}
		current = current->next;
	}

	integrate(ImGui::GetIO().DeltaTime);

	generateContacts();
}