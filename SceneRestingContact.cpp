#include "./SceneRestingContact.h"

SceneRestingContact::SceneRestingContact():
	m_title("SceneRestingContact"),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL),
	m_wall(NULL),
	m_speed(1.0f),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f))),
	m_contactResolver(ObjectContact()){
}

SceneRestingContact::SceneRestingContact(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneRestingContact"),
	m_speed(1.0f),
	m_shader(shader),
	m_texture(texture),
	m_contactResolver(ObjectContact()),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,-10.0f))){
	
	m_player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_player->addVertices(vertices);
	m_player->createAABB(BBType::AxisAligned);
	m_player->addRigidBody2D(new RigidBody2D(5.0f));

	m_wall = new Object(
		glm::vec3(0.0f,-100.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(20.0f,1.0f,1.0f)
	);
	m_wall->addVertices(vertices);
	m_wall->createAABB(BBType::AxisAligned);
	m_wall->addRigidBody2D(new RigidBody2D(5.0f));


}

SceneRestingContact::~SceneRestingContact(){
	delete m_player;
}

void SceneRestingContact::render(Window* window){
	StaticRenderer::bind();
	m_shader->use();
	m_texture->bind();
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCameraController()->getViewMatrix());
	
	m_shader->setUniformMat4f("u_model",m_player->getModelMatrix());
	StaticRenderer::renderObject();

	m_shader->setUniformMat4f("u_model",m_wall->getModelMatrix());
	StaticRenderer::renderObject();
	
	m_texture->unbind();
	StaticRenderer::unbind();
}

void SceneRestingContact::update(Window* window){
	input(window);

	m_forceGravity.updateForce(m_player,ImGui::GetIO().DeltaTime);

	Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);
	Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);

	Collision col0 = AABB::getCollision(m_player->getBoundingBox(),m_wall->getBoundingBox());

	if(col0.colliding){
		m_contactResolver.object[0] = m_player;
		m_contactResolver.object[1] = NULL;
		m_contactResolver.m_restitution = 0.0f;
		m_contactResolver.m_contactNormal = col0.collisionNormal;
		m_contactResolver.resolve(ImGui::GetIO().DeltaTime,col0);
	}
}

void SceneRestingContact::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneRestingContact::input(Window* window){
	
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_UP)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_DOWN)){
		
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_LEFT)){
		
	}
	
	
}

std::string SceneRestingContact::getSceneTitle() const {
	return m_title;
}
