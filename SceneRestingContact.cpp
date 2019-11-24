#include "./SceneRestingContact.h"

SceneRestingContact::SceneRestingContact():
	m_title("SceneRestingContact"),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL),
	m_restingObject(NULL),
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
	m_forceGravity(ForceGravity(glm::vec2(0.0f, Physics2D::G * -5.0f))){
	
	m_player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_player->addVertices(vertices);
	m_player->createAABB(BBType::AxisAligned);
	m_player->addRigidBody2D(new RigidBody2D(5.0f));

	m_restingObject = new Object(
		glm::vec3(20.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_restingObject->addVertices(vertices);
	m_restingObject->createAABB(BBType::AxisAligned);
	m_restingObject->addRigidBody2D(new RigidBody2D(5.0f));

	m_wall = new Object(
		glm::vec3(0.0f,-100.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(20.0f,1.0f,1.0f)
	);
	m_wall->addVertices(vertices);
	m_wall->createAABB(BBType::AxisAligned);
	m_wall->addRigidBody2D(new RigidBody2D(-1.0f));


}

SceneRestingContact::~SceneRestingContact(){
	delete m_player;
	delete m_restingObject;
	delete m_wall;
}

void SceneRestingContact::render(Window* window){
	StaticRenderer::bind();
	m_shader->use();
	m_texture->bind();
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCameraController()->getViewMatrix());
	
	m_shader->setUniformMat4f("u_model",m_player->getModelMatrix());
	StaticRenderer::renderObject();

	m_shader->setUniformMat4f("u_model",m_restingObject->getModelMatrix());
	StaticRenderer::renderObject();

	m_shader->setUniformMat4f("u_model",m_wall->getModelMatrix());
	StaticRenderer::renderObject();
	
	m_texture->unbind();
	StaticRenderer::unbind();
}

void SceneRestingContact::update(Window* window){
	input(window);

	m_forceGravity.updateForce(m_player,ImGui::GetIO().DeltaTime);
	m_forceGravity.updateForce(m_restingObject,ImGui::GetIO().DeltaTime);

	Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);
	Physics2D::integrator3(m_restingObject,ImGui::GetIO().DeltaTime);

	Collision col0 = AABB::getCollision(m_wall->getBoundingBox(),m_player->getBoundingBox());

	if(col0.colliding){
		m_contactResolver.object[0] = m_player;
		m_contactResolver.object[1] = NULL;
		m_contactResolver.m_restitution = 1.0f;
		m_contactResolver.m_contactNormal = col0.collisionNormal;
		m_contactResolver.resolve(ImGui::GetIO().DeltaTime,col0);
	}

	Collision col1 = AABB::getCollision(m_wall->getBoundingBox(),m_restingObject->getBoundingBox());

	if(col1.colliding){
		m_contactResolver.object[0] = m_restingObject;
		//object[1] is already NULL
		m_contactResolver.m_restitution = 0.0f; //don't believe it needs to be zero, but just in case
		m_contactResolver.m_contactNormal = col1.collisionNormal;
		m_contactResolver.resolveRestingContact(ImGui::GetIO().DeltaTime,col1);
	}
}

void SceneRestingContact::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneRestingContact::input(Window* window){
	glm::vec2 velocity(0.0f,0.0f);
	glm::vec2 position = m_restingObject->getPos2();
	float speed = 1.0f;
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_UP)){
		
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_DOWN)){
		
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT)){
		position.x += speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_LEFT)){
		position.x -= speed;
	}
	
	m_restingObject->setPos(position);
	
}

std::string SceneRestingContact::getSceneTitle() const {
	return m_title;
}
