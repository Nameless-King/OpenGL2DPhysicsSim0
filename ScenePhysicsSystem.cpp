#include "./ScenePhysicsSystem.h"

static bool mouseButton1Down = false;
static bool mouseButton2Down = false;

ScenePhysicsSystem::ScenePhysicsSystem():
	m_title("ScenePhysicsSystem"),
	m_shader(NULL),
	m_texture(NULL),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 1.0f))),
	m_collisionResolver(new CollisionBatchResolver(1)),
	m_tempContact(ObjectContact()),
	m_numCollisions(0),
	m_numObjects(0){
}

ScenePhysicsSystem::ScenePhysicsSystem(Shader* shader, Texture* texture, const float vertices[]):
	m_title("ScenePhysicsSystem"),
	m_shader(shader),
	m_texture(texture),
	m_maxContacts(0),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 0.0f))),
	m_collisionResolver(new CollisionBatchResolver(1)),
	m_tempContact(ObjectContact()),
	m_numCollisions(0),
	m_numObjects(0){

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
	ImGui::Text("Number of objects: %d",m_numObjects);
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

	//creates infinite mass objects upon left click at mouse position
	int mouseButton1Pressed = glfwGetMouseButton(window->getWindow(),GLFW_MOUSE_BUTTON_1);
	if( mouseButton1Pressed == GLFW_TRUE && !mouseButton1Down){
			mouseButton1Down = true;

			double posX = 0;
			double posY = 0;
			glfwGetCursorPos(window->getWindow(),&posX,&posY);

			posX -= window->getWidth() / 2.0f;
			posY = window->getHeight() / 2.0f - posY;

			posX /= window->getZoom() / 2.0f;
			posY /= window->getZoom() / 2.0f;

			int camX = window->getCameraController()->getCameraPos().x;
			int camY = window->getCameraController()->getCameraPos().y;

			posX += camX;
			posY += camY;

			Object* newObject = new Object(
				glm::vec3(posX,posY,0.0f),
				glm::vec3(0.0f,0.0f,0.0f),
				glm::vec3(1.0f,1.0f,1.0f)
			);
			newObject->addVertices(StaticRenderer::getVertices());
			newObject->createHitbox(HitboxType::AxisAligned);
			newObject->addRigidBody2D(new RigidBody2D(-1.0f));

			addObject(newObject);

		}else if(mouseButton1Pressed == GLFW_FALSE && mouseButton1Down){
			mouseButton1Down = false;
		}

		//creates finite mass objects upon right click at mouse position
		int mouseButton2Pressed = glfwGetMouseButton(window->getWindow(),GLFW_MOUSE_BUTTON_2);
		if( mouseButton2Pressed == GLFW_TRUE && !mouseButton2Down){
			mouseButton2Down = true;

			double posX = 0;
			double posY = 0;
			glfwGetCursorPos(window->getWindow(),&posX,&posY);

			posX -= window->getWidth() / 2.0f;
			posY = window->getHeight() / 2.0f - posY;

			posX /= window->getZoom() / 2.0f;
			posY /= window->getZoom() / 2.0f;

			int camX = window->getCameraController()->getCameraPos().x;
			int camY = window->getCameraController()->getCameraPos().y;

			posX += camX;
			posY += camY;

			Object* newObject = new Object(
				glm::vec3(posX,posY,0.0f),
				glm::vec3(0.0f,0.0f,0.0f),
				glm::vec3(1.0f,1.0f,1.0f)
			);
			newObject->addVertices(StaticRenderer::getVertices());
			newObject->createHitbox(HitboxType::AxisAligned);
			newObject->addRigidBody2D(new RigidBody2D(1.0f));

			addObject(newObject);

		}else if(mouseButton2Pressed == GLFW_FALSE && mouseButton2Down){
			mouseButton2Down = false;
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
			if(!(ObjectContact::hasInfiniteMass(hitter->object)==ObjectContact::hasInfiniteMass(hittee->object) && ObjectContact::hasInfiniteMass(hitter->object))){
				//Order doesn't matter for detectContact
				ObjectContact generatedContact = ObjectContact::detectContact(hittee->object->getHitbox(),hitter->object->getHitbox());
				if(generatedContact.m_colliding){
					
					//Order does motter for object[0] and object[1] of ObjectContact
					m_tempContact.object[0] = hittee->object;
					m_tempContact.object[1] = hitter->object;
					//std::cout << hitter->object->getRigidBody2D()->getMass() << " " << hittee->object->getRigidBody2D()->getMass() << std::endl;
					m_tempContact.m_restitution = 0.0f;
					m_tempContact.m_penetrationDepth = generatedContact.m_penetrationDepth;
					//Order does matter for obj1 and obj2 of testBoxCollision
					testBoxCollision(hittee->object,hitter->object,&generatedContact);
					m_tempContact.m_contactNormal = generatedContact.m_contactNormal;
					
					m_tempContact.resolve(ImGui::GetIO().DeltaTime);
					m_collisionResolver->registerContact(m_tempContact);
				}
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
	
	//m_collisionResolver->resolveContacts(ImGui::GetIO().DeltaTime);
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

	m_numObjects++;
}

void ScenePhysicsSystem::testBoxCollision(Object* obj1, Object* obj2, ObjectContact* col){
	if(ObjectContact::hasInfiniteMass(obj1)){
		Object* temp = obj2;
		obj2 = obj1;
		obj1 = temp;
	}
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
	//std::cout << col->m_contactNormal.x << " " << col->m_contactNormal.y << std::endl;
}