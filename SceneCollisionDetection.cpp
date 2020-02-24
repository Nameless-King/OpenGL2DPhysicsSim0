#include "./SceneCollisionDetection.h"

SceneCollisionDetection::SceneCollisionDetection():
	m_title("SceneCollisionDetection"),
	m_shader(NULL),
	m_texture(NULL),
	m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 1.0f))),
	m_collisionResolver(new CollisionBatchResolver(1)),
	m_tempContact(ObjectContact()),
	m_numCollisions(0),
	m_numObjects(0),
	m_player(NULL){
}

SceneCollisionDetection::SceneCollisionDetection(Shader* shader, Texture* texture, const float vertices[]):
	m_title("SceneCollisionDetection"),
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

	Object* obb1 = new Object(
		glm::vec3(20.0f,20.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	obb1->addVertices(vertices);
	obb1->addRigidBody2D(new RigidBody2D(1.0f));
	obb1->addOBB();

	Object* obb2 = new Object(
		glm::vec3(-20.0f,-20.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	);
	obb2->addVertices(vertices);
	obb2->addRigidBody2D(new RigidBody2D(1.0f));
	obb2->addOBB();

	addObject(obb1);
	addObject(obb2);

	m_player = obb1;

}

SceneCollisionDetection::~SceneCollisionDetection(){
	ObjectRegistration* currentRegistry = m_firstObject;
	while(currentRegistry){
		delete currentRegistry->object;
		currentRegistry = currentRegistry->next;
	}
	delete m_collisionResolver;
}

void SceneCollisionDetection::render(Window* window){
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

void SceneCollisionDetection::update(Window* window){
	runPhysics(ImGui::GetIO().DeltaTime);
	
	input(window);
}

void SceneCollisionDetection::renderGUI(){
	ImGui::Begin(m_title.c_str());
	ImGui::Text("Number of collision: %d",m_numCollisions);
	ImGui::Text("Number of objects: %d",m_numObjects);
	ImGui::End();
}

void SceneCollisionDetection::input(Window* window){
	
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

	if(glfwGetKey(window->getWindow(),GLFW_KEY_R)){
		m_player->setRot(
			0.0f,
			0.0f,
			m_player->getRotationXYZ().z + 0.5f
		);


		//readjusts the size of the AABB to fully encapsulate the rotated object
		{
			float rotZ = m_player->getRotationXYZ().z;
			glm::mat2 m = EngineMaths::getRotationMatrix(rotZ);
			//m[0][0] = cos((PI/180)*rotZ);
			//m[0][1] = -sin((PI/180)*rotZ);
			//m[1][0] = sin((PI/180)*rotZ);
			//m[1][1] = cos((PI/180)*rotZ);
			
			float extents[2];
			for(int i = 0;i<2;i++){
				for(int j = 0;j<2;j++){
					//if not multiplied by constant(default extents) or it will exponentially increase
					extents[i] += abs(m[i][j]) * 5.0f;// (m_player->getHitbox().getHalfExtents()[j]);
				}
			}
			m_player->setHalfExtents(extents[0],extents[1]);
		}

	}
	
	
	
}

std::string SceneCollisionDetection::getSceneTitle() const {
	return m_title;
}

void SceneCollisionDetection::startFrame(){
	ObjectRegistration* currentRegister = m_firstObject;

	while(currentRegister){
		currentRegister->object->getRigidBody2D()->zeroForce();
		currentRegister = currentRegister -> next;
	}
}

void SceneCollisionDetection::generateContacts(){
	ObjectRegistration* hittee = m_firstObject;
	while(hittee){
		ObjectRegistration* hitter = hittee->next;
		while(hitter){
			if(!(ObjectContact::hasInfiniteMass(hitter->object)==ObjectContact::hasInfiniteMass(hittee->object)&&
			ObjectContact::hasInfiniteMass(hitter->object))){
				bool areOriented = hittee->object->getOBB();
				bool areOriented1 = hitter->object->getOBB();
				if(!areOriented && !areOriented1 && ObjectContact::isColliding(hittee->object->getHitbox(),hitter->object->getHitbox())){
					ObjectContact generatedContact = ObjectContact::detectContact(hittee->object->getHitbox(),hitter->object->getHitbox());

					m_tempContact.object[0] = hittee->object;
					m_tempContact.object[1] = hitter->object;

					m_tempContact.m_restitution = 0.0f;
					m_tempContact.m_penetrationDepth = generatedContact.m_penetrationDepth;

					testBoxCollision(hittee->object, hitter->object,&generatedContact);

					m_tempContact.m_contactNormal = generatedContact.m_contactNormal;

					m_tempContact.resolve(ImGui::GetIO().DeltaTime);
					m_collisionResolver->registerContact(m_tempContact);
				}else if(areOriented && areOriented1){
					bool colliding = ObjectContact::isColliding(
						hittee->object->getOBB(),
					 	hitter->object->getOBB()
					);

					std::cout << colliding << std::endl;
				}
			}
			hitter = hitter->next;
		}
		hittee = hittee->next;
	}
}

void SceneCollisionDetection::integrate(float dt){
	ObjectRegistration* currentRegister = m_firstObject;
	while(currentRegister){
		Physics2D::integrator3(currentRegister->object,dt);
		currentRegister = currentRegister->next;
	}
}

void SceneCollisionDetection::runPhysics(float dt){
	
	ObjectRegistration* currentRegister = m_firstObject;
	while(currentRegister){
		m_forceGravity.updateForce(currentRegister->object,ImGui::GetIO().DeltaTime);
		currentRegister = currentRegister->next;
	}

	integrate(ImGui::GetIO().DeltaTime);

	generateContacts();
	
	m_numCollisions = m_collisionResolver->numOfCollisions();
	m_collisionResolver->resetRegistry();
}

void SceneCollisionDetection::addObject(Object* newObject){
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

void SceneCollisionDetection::testBoxCollision(Object* obj1, Object* obj2, ObjectContact* col){
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