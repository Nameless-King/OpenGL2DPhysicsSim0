#include "./SceneForceGenerator.h"

SceneForceGenerator::SceneForceGenerator():
	m_title("SceneForceGenerator"),
	m_active(false),
	m_springConstant(2.0f),
	m_useGravity(false),
	m_shader(NULL),
	m_texture(NULL),
	m_staticObj(NULL),
	m_hangingObj(NULL),
	m_forceSpring(ForceSpring()),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,-10.0f))){}
	
SceneForceGenerator::SceneForceGenerator(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneForceGenerator"),
	m_active(false),
	m_springConstant(2.0f),
	m_useGravity(false),
	m_shader(shader),
	m_texture(texture),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,-20.0f))){
			
	m_staticObj = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	m_staticObj->addVertices(vertices);
	m_staticObj->createAABB(BBType::Circle);
	
	RigidBody2D* rbStatic = new RigidBody2D(5.0f);
	rbStatic->setDamping(1.0f);
	
	m_staticObj->addRigidBody2D(rbStatic);
	
	m_hangingObj = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	
	m_hangingObj->addVertices(vertices);
	m_hangingObj->createAABB(BBType::Circle);
	
	RigidBody2D* rbHanging = new RigidBody2D(5.0f);
	rbHanging->setDamping(0.5f);
	
	m_hangingObj->addRigidBody2D(rbHanging);

	float kConstant = 0.1f;
	float equilibrium = 20.0f;
	m_forceSpring = ForceSpring(m_staticObj,kConstant,equilibrium);
};

SceneForceGenerator::~SceneForceGenerator(){
	delete m_staticObj;
	delete m_hangingObj;
}

std::string SceneForceGenerator::getSceneTitle() const{
	return m_title;
}

bool SceneForceGenerator::isActive() const{
	return m_active;
}

void SceneForceGenerator::render(Window* window){
	StaticRenderer::bind();
	
	m_shader->use();
	m_texture->bind();
	
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));
	
	m_shader->setUniformMat4f("u_model",m_staticObj->getModelMatrix());
	StaticRenderer::renderObject();
	
	m_shader->setUniformMat4f("u_model",m_hangingObj->getModelMatrix());
	StaticRenderer::renderObject();
	
	m_texture->unbind();
	
	StaticRenderer::unbind();
}

void SceneForceGenerator::update(Window* window){
	input(window);

	m_forceGravity.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
	m_forceSpring.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);

	Physics2D::integrator2(m_hangingObj,ImGui::GetIO().DeltaTime);
}

void SceneForceGenerator::setActive(bool active){
	
}

void SceneForceGenerator::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}
	
void SceneForceGenerator::input(Window* window){
	float px = m_staticObj->getPos().x;
	float py = m_staticObj->getPos().y;
	float speed = 5.0f;

	if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
		py += speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
		py -= speed;
	}

	if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
		px += speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
		px -= speed;
	}

	m_staticObj->setPos(px,py);

}