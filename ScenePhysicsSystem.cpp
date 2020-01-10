#include "./ScenePhysicsSystem.h"

ScenePhysicsSystem::ScenePhysicsSystem():
	m_title("ScenePhysicsSystem"),
	m_shader(NULL),
	m_texture(NULL),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 0.0f))),
	m_collisionResolver(new CollisionBatchResolver(1)),
	m_tempContact(ObjectContact()),
	m_numCollisions(0){
}

ScenePhysicsSystem::ScenePhysicsSystem(Shader* shader, Texture* texture, const float vertices[]):
	m_title("ScenePhysicsSystem"),
	m_shader(shader),
	m_texture(texture),
	m_maxContacts(0),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 0.0f))),
	m_collisionResolver(new CollisionBatchResolver(1)),
	m_tempContact(ObjectContact()),
	m_numCollisions(0){

	m_firstObject = new ObjectRegistration();

	Object* player = new Object(
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	player->addVertices(vertices);
	player->createHitbox(HitboxType::AxisAligned);
	player->addRigidBody2D(new RigidBody2D(5.0f));

	addObject(player);
	m_player = player;

	Object* floor = new Object(
		glm::vec3(0.0f,-300.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(30.0f,1.0f,1.0f)
	);
	floor->addVertices(vertices);
	floor->createHitbox(HitboxType::AxisAligned);
	floor->addRigidBody2D(new RigidBody2D(-1.0f));

	addObject(floor);
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
	ImGui::Text("Number of collision: %d",m_numCollisions);
	ImGui::End();
}

void ScenePhysicsSystem::input(Window* window){
	glm::vec2 velocity(0.0f,0.0f);
	float speed = 100.0f;
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_UP)){
		velocity.y = speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_DOWN)){
		velocity.y = -speed;
	}else{
		velocity.y = 0.0f;
	}
	
	
	if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT)){
		velocity.x = speed;
	}else if(glfwGetKey(window->getWindow(),GLFW_KEY_LEFT)){
		velocity.x = -speed;
	}else{
		velocity.x = 0.0f;
	}
	
	m_player->getRigidBody2D()->setVelocity(velocity);
	
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
			ObjectContact generatedContact = ObjectContact::detectContact(hitter->object->getHitbox(),hittee->object->getHitbox());
			if(generatedContact.m_colliding){
				
				m_tempContact.object[0] = hitter->object;
				m_tempContact.object[1] = hittee->object;
				m_tempContact.m_restitution = 0.0f;
				testBoxCollision(hitter->object,hittee->object,&generatedContact);
				m_tempContact.m_penetrationDepth = generatedContact.m_penetrationDepth;
				m_tempContact.m_contactNormal = generatedContact.m_contactNormal;
				
				m_collisionResolver->registerContact(m_tempContact);
			}
			hitter = hitter->next;
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
	ObjectRegistration* currentRegister = m_firstObject;
	while(currentRegister){
		m_forceGravity.updateForce(currentRegister->object,ImGui::GetIO().DeltaTime);
		currentRegister = currentRegister->next;
	}


	//integrate forces and update positions
	integrate(ImGui::GetIO().DeltaTime);

	//generate contacts
	generateContacts();

	//process contacts
	
	m_collisionResolver->resolveContacts(ImGui::GetIO().DeltaTime);
	m_numCollisions = m_collisionResolver->numOfCollisions();
	m_collisionResolver->resetRegistry();
}

void ScenePhysicsSystem::addObject(Object* newObject){
	if(!m_firstObject->object){
		m_firstObject->object = newObject;
	}else{
		ObjectRegistration* lastRegistry = new ObjectRegistration();
		lastRegistry->object = newObject;
		ObjectRegistration* currentRegistry = m_firstObject;
		while(currentRegistry->next){
			currentRegistry = currentRegistry->next;
		}
		currentRegistry->next = lastRegistry;
	}
}

void ScenePhysicsSystem::testBoxCollision(Object* obj1, Object* obj2, ObjectContact* col){
	if(col->m_distance.x  / (obj1->getScaleXYZ().x * obj2->getScaleXYZ().x)> col->m_distance.y / (obj1->getScaleXYZ().y * obj2->getScaleXYZ().y)){
		if(obj1->getPositionXY().x > obj2->getPositionXY().x){
			col->m_contactNormal.x = 1;
			col->m_contactNormal.y = 0;
		}else{
			col->m_contactNormal.x = -1;
			col->m_contactNormal.y = 0;
		}
	}else{
		if(obj1->getPositionXY().y > obj2->getPositionXY().y){
			col->m_contactNormal.x = 0;
			col->m_contactNormal.y = 1;
		}else{
			col->m_contactNormal.x = 0;
			col->m_contactNormal.y = -1;
		}
	}
	
}