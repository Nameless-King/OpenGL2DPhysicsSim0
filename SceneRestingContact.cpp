#include "./SceneRestingContact.h"

static bool mouse1Pressed = false;

SceneRestingContact::SceneRestingContact():
	m_title("SceneRestingContact"),
	m_shader(NULL),
	m_texture(NULL),
	m_player(NULL),
	m_restingObject(NULL),
	m_wall(NULL),
	m_speed(1.0f),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f))),
	m_contactResolver(ObjectContact()),
	m_collisionBatchResolver(CollisionBatchResolver(1)){
}

SceneRestingContact::SceneRestingContact(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneRestingContact"),
	m_speed(1.0f),
	m_shader(shader),
	m_texture(texture),
	m_contactResolver(ObjectContact()),
	m_forceGravity(ForceGravity(glm::vec2(0.0f, Physics2D::G * -5.0f))),
	m_collisionBatchResolver(CollisionBatchResolver(1)){
	
	m_player = new Object(
		glm::vec3(20.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	m_player->addVertices(vertices);
	m_player->createAABB(BBType::AxisAligned);
	m_player->addRigidBody2D(new RigidBody2D(5.0f));

	m_restingObject = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
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
	for(int i = 0;i<m_objects.size();i++){
		delete m_objects[i];
	}
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

	for(int i = 0;i<m_objects.size();i++){
		m_shader->setUniformMat4f("u_model",m_objects[i]->getModelMatrix());
		StaticRenderer::renderObject();
	}
	
	m_texture->unbind();
	StaticRenderer::unbind();
}

void SceneRestingContact::update(Window* window){
	input(window);

	m_forceGravity.updateForce(m_restingObject,ImGui::GetIO().DeltaTime);
	//m_forceGravity.updateForce(m_player,ImGui::GetIO().DeltaTime);
	for(int i = 0;i<m_objects.size();i++){
		m_forceGravity.updateForce(m_objects[i],ImGui::GetIO().DeltaTime);
	}
	
	Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);
	Physics2D::integrator3(m_restingObject,ImGui::GetIO().DeltaTime);
	for(int i = 0;i<m_objects.size();i++){
		Physics2D::integrator3(m_objects[i],ImGui::GetIO().DeltaTime);
	}

	Collision col0 = AABB::getCollision(m_wall->getBoundingBox(),m_player->getBoundingBox());

	if(col0.colliding){
		m_contactResolver.object[0] = m_player;
		m_contactResolver.object[1] = NULL;
		m_contactResolver.m_restitution = 0.0f;
		testBoxCollision(m_player,m_wall,&col0);
		m_contactResolver.m_collision = col0;
		m_contactResolver.m_penetrationDepth = col0.penetrationDepth;
		m_contactResolver.m_contactNormal = col0.collisionNormal;
		m_collisionBatchResolver.registerContact(m_contactResolver);
	}

	Collision col1 = AABB::getCollision(m_wall->getBoundingBox(),m_restingObject->getBoundingBox());

	if(col1.colliding){
		m_contactResolver.object[0] = m_restingObject;
		m_contactResolver.object[1] = NULL;
		m_contactResolver.m_restitution = 0.0f; //don't believe it needs to be zero, but just in case
		testBoxCollision(m_restingObject,m_wall,&col1);
		m_contactResolver.m_collision = col1;
		m_contactResolver.m_penetrationDepth = col1.penetrationDepth;
		m_contactResolver.m_contactNormal = col1.collisionNormal;
		m_collisionBatchResolver.registerContact(m_contactResolver);
	}

	Collision col2 = AABB::getCollision(m_restingObject->getBoundingBox(),m_player->getBoundingBox());

	if(col2.colliding){
		m_contactResolver.object[0] = m_player;
		m_contactResolver.object[1] = m_restingObject;
		m_contactResolver.m_restitution = 0.0f;
		testBoxCollision(m_player,m_restingObject,&col2);
		m_contactResolver.m_collision = col2;
		m_contactResolver.m_penetrationDepth = col2.penetrationDepth;
		m_contactResolver.m_contactNormal = col2.collisionNormal;
		m_collisionBatchResolver.registerContact(m_contactResolver);
	}


	for(int i = 0;i<m_objects.size();i++){
		for(int j = i+1;j<m_objects.size();j++){
			Collision col3 = AABB::getCollision(m_objects[i]->getBoundingBox(),m_objects[j]->getBoundingBox());

			if(col3.colliding){
				m_contactResolver.object[0] = m_objects[j];
				m_contactResolver.object[1] = m_objects[i];
				m_contactResolver.m_restitution = 0.0f;
				testBoxCollision(m_objects[j],m_objects[i],&col3);
				m_contactResolver.m_collision = col3;
				m_contactResolver.m_penetrationDepth = col3.penetrationDepth;
				m_contactResolver.m_contactNormal = col3.collisionNormal;
				m_collisionBatchResolver.registerContact(m_contactResolver);
			}
		}
	}

	
	m_collisionBatchResolver.resolveContacts(ImGui::GetIO().DeltaTime);
	m_collisionBatchResolver.resetRegistry();

	boundCheck(window,m_restingObject);
	boundCheck(window,m_player);
	for(int i = 0;i<m_objects.size();i++){
		boundCheck(window,m_objects[i]);
	}
}

void SceneRestingContact::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::End();
}

void SceneRestingContact::input(Window* window){
	glm::vec2 velocity(0.0f,0.0f);
	glm::vec2 position = m_player->getPos2();
	float speed = 100.0f;
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_UP)){
		position.y += speed;
		velocity.y = speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_DOWN)){
		position.y -= speed;
		velocity.y = -speed;
	}else{
		velocity.y = 0.0f;
	}
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT)){
		position.x += speed;
		velocity.x = speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_LEFT)){
		position.x -= speed;
		velocity.x = -speed;
	}else{
		velocity.x = 0.0f;
	}
	//m_player->setPos(position);
	m_player->getRigidBody2D()->setVelocity(velocity);

	int mousePressed = glfwGetMouseButton(window->getWindow(),GLFW_MOUSE_BUTTON_1);

	if(mousePressed == GLFW_TRUE && !mouse1Pressed){
		mouse1Pressed = true;

		double posX = 0;
		double posY = 0;
		glfwGetCursorPos(window->getWindow(),&posX,&posY);
		
		posX -= window->getWidth()/2.0f;
		posY = window->getHeight()/2.0f - posY;
		m_objects.push_back(new Object(
			glm::vec3(posX,posY,0.0f),
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(1.0f,1.0f,1.0f)
		));
		int newIndex = m_objects.size() - 1;
		m_objects[newIndex]->addVertices(StaticRenderer::getVertices());
		m_objects[newIndex]->createAABB(BBType::AxisAligned);
		m_objects[newIndex]->addRigidBody2D(new RigidBody2D(5.0f));
		
	}else if(mousePressed == GLFW_FALSE && mouse1Pressed){
		mouse1Pressed = false;
	}
	
}

std::string SceneRestingContact::getSceneTitle() const {
	return m_title;
}


void SceneRestingContact::boundCheck(Window* window, Object* object){
	glm::vec2* vel = object->getRigidBody2D()->getVelocity();
	glm::vec2 pos = object->getPos();
	if(pos.y < window->getHeight()/-2.0f + 5.0f){
		object->getRigidBody2D()->setVelocity(0.0f,0.0f);
		object->setPos(pos.x,window->getHeight()/-2.0f + 5.0f);
	}
}

void SceneRestingContact::testBoxCollision(Object* obj1, Object* obj2, Collision* col){
	if(col->distance.x  / (obj1->getScl().x * obj2->getScl().x)> col->distance.y / (obj1->getScl().y * obj2->getScl().y)){
		if(obj1->getPos2().x > obj2->getPos2().x){
			col->collisionNormal.x = 1;
			col->collisionNormal.y = 0;
		}else{
			col->collisionNormal.x = -1;
			col->collisionNormal.y = 0;
		}
	}else{
		if(obj1->getPos2().y > obj2->getPos2().y){
			col->collisionNormal.x = 0;
			col->collisionNormal.y = 1;
		}else{
			col->collisionNormal.x = 0;
			col->collisionNormal.y = -1;
		}
	}
	
}