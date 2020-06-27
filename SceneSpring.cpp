#include "./SceneSpring.h"

SceneSpring::SceneSpring():
	Scene("SceneSpring"),
	m_springConstant(2.0f),
	m_useGravity(false),
	m_shader(NULL),
	m_texture(NULL),
	m_staticObj(NULL),
	m_hangingObj(NULL),
	m_forceSpring(ForceSpring()),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,-10.0f))),
	m_forceBungee(ForceBungee()),
	m_forceFakeSpring(ForceFakeSpring()),
	m_currentType(0){}
	
SceneSpring::SceneSpring(Shader* shader, Texture* texture):
	Scene("SceneSpring"),
	m_springConstant(2.0f),
	m_useGravity(false),
	m_shader(shader),
	m_texture(texture),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f))),
	m_currentType(2){
			
	m_staticObj = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_staticObj->createBound(BoundingType::Circle);
	m_staticObj->addRigidbody2D(new Rigidbody2D(1.0f));
	
	
	m_hangingObj = new Object(
		glm::vec3(0.0f,-10.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_hangingObj->createBound(BoundingType::Circle);
	m_hangingObj->addRigidbody2D(new Rigidbody2D(1.0f));

	addObject(m_staticObj);
	addObject(m_hangingObj);

	float kConstant = 100.0f;
	float equilibrium = 100.0f;
	m_forceSpring = ForceSpring(m_staticObj,kConstant,equilibrium);

	float bkc = 100.0f;
	float be = 100.0f;
	m_forceBungee = ForceBungee(m_staticObj,bkc,be);

	m_forceFakeSpring = ForceFakeSpring(m_staticObj,50.0f,0.05f);
};

SceneSpring::~SceneSpring(){}


void SceneSpring::render(GWindow* window){
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

void SceneSpring::update(GWindow* window){
	startFrame();
	runPhysics(ImGui::GetIO().DeltaTime);
	input(window);

}

void SceneSpring::renderGUI(){
	float gravity = m_forceGravity.getGravity().y;
	float equilibrium = m_forceSpring.getEquilibrium();
	float springConstant = m_forceSpring.getSpringConstant();
	float bungeeEquilibrium = m_forceBungee.getEquilibrium();
	float bungeeSpringConstant = m_forceBungee.getSpringConstant();
	float stiffSpringConstant = m_forceFakeSpring.getSpringConstant();
	float stiffDamping = m_forceFakeSpring.getDamping();
	int currentType = m_currentType;

	ImGui::Begin(m_title.c_str());
	if(ImGui::DragFloat("Gravity", &gravity, 0.1f)){
		m_forceGravity.setGravity(0.0f,gravity);
	}

	switch(m_currentType){
		case 0:
			if(ImGui::DragFloat("Equilibrium",&equilibrium,0.1f)){
				m_forceSpring.setEquilibrium(equilibrium);
			}
			if(ImGui::DragFloat("Spring Constant (k)",&springConstant,0.01f)){
				m_forceSpring.setSpringConstant(springConstant);
			}
			break;
		case 1:
			if(ImGui::DragFloat("Bungee Equilibrium",&bungeeEquilibrium,0.1f)){
				m_forceBungee.setEquilibrium(bungeeEquilibrium);
			}
			if(ImGui::DragFloat("Bungee Spring Constant",&bungeeSpringConstant,0.01f)){
				m_forceBungee.setSpringConstant(bungeeSpringConstant);
			}
			break;
		case 2:
			if(ImGui::DragFloat("Spring Constant",&stiffSpringConstant,0.1f)){
				m_forceFakeSpring.setSpringConstant(stiffSpringConstant);
			}
			if(ImGui::DragFloat("Damping",&stiffDamping,0.01f)){
				m_forceFakeSpring.setDamping(stiffDamping);
			}
			break;
		default:
			break;
	}
	
	

	ImGui::RadioButton("Spring",&currentType,0);
	ImGui::SameLine();
	ImGui::RadioButton("Bungee",&currentType,1);
	ImGui::SameLine();
	ImGui::RadioButton("Stiff Spring",&currentType,2);

	if(m_currentType != currentType){
		m_currentType = currentType;
	}

	ImGui::End();
}
	
void SceneSpring::input(GWindow* window){
	float px = m_staticObj->getPositionXYZ().x;
	float py = m_staticObj->getPositionXYZ().y;
	float speed = 5.0f;

	if(GInput::isKeyDown(GLFW_KEY_UP)){
		py += speed;
	}else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
		py -= speed;
	}

	if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
		px += speed;
	}else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
		px -= speed;
	}

	m_staticObj->setPos(px,py);

}

void SceneSpring::runPhysics(float dt, GWindow* window){

	m_forceGravity.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
	switch(m_currentType){
		case 0:
			m_forceSpring.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
			break;
		case 1:
			m_forceBungee.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
			break;
		case 2:
			m_forceFakeSpring.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
			break;
		default:
			break;
	}

	integrate(ImGui::GetIO().DeltaTime);

	generateContacts();
}