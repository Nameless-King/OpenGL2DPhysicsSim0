#include "./SceneOBB.h"

SceneOBB::SceneOBB():
    Scene("SceneOBB"),
    m_shader(NULL),
    m_texture(NULL),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 1.0f))),
    m_collisionResolver(new CollisionBatchResolver(1)),
    m_numCollisions(0),
    m_numObjects(0){
}

SceneOBB::SceneOBB(Shader* shader, Texture* texture):
    Scene("SceneOBB"),
    m_shader(shader),
    m_texture(texture),
    m_maxContacts(0),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 1.0f))),
    m_collisionResolver(new CollisionBatchResolver(1)),
    m_numCollisions(0),
    m_numObjects(0){
        m_firstObject = new ObjectRegistration();

        Object* player = new Object(
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );
        player->createBound(BoundingType::Oriented);
        player->addRigidbody2D(new Rigidbody2D(5.0f));
        addObject(player);
        m_player = player;

        Object* testBlock = new Object(
            glm::vec3(0.0f,-10.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );
        testBlock->createBound(BoundingType::Oriented);
        testBlock->addRigidbody2D(new Rigidbody2D(-1.0f));
        addObject(testBlock);
        m_test = testBlock;

        testBlock = new Object(
            glm::vec3(0.0f,-50.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(2.0f,1.0f,1.0f)
        );
        testBlock->createBound(BoundingType::Oriented);
        testBlock->addRigidbody2D(new Rigidbody2D(-1.0f));
        addObject(testBlock);


    }

    SceneOBB::~SceneOBB(){
    ObjectRegistration* currentRegistry = m_firstObject;
    while(currentRegistry){
        delete currentRegistry->object;
        currentRegistry = currentRegistry->next;
    }
    delete m_collisionResolver;
}

void SceneOBB::render(GWindow* window){
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

void SceneOBB::update(GWindow* window){

    runPhysics(ImGui::GetIO().DeltaTime);
    input(window);
}

void SceneOBB::renderGUI(){
    ImGui::Begin(getSceneTitle().c_str());
    ImGui::Text("Number of collision: %d",m_numCollisions);
    ImGui::Text("Number of objects: %d",m_numObjects);
    ImGui::End();
}

void SceneOBB::input(GWindow* window){
    glm::vec2 velocity(0.0f,0.0f);
    float speed = 10.0f;

    if(GInput::isKeyDown(GLFW_KEY_UP)){
        velocity.y = speed;
    }else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
        velocity.y = -speed;
    }

    if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
        velocity.x = speed;
    }else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
        velocity.x = -speed;
    }

    m_player->getRigidbody2D()->setVelocity(velocity);

    if(GInput::isKeyDown(GLFW_KEY_R)){
       m_player->rotateDegrees(0.5f);
    }

    if(GInput::isKeyDown(GLFW_KEY_C)){
        m_test->rotateDegrees(0.5f);
    }
}

void SceneOBB::startFrame(){
    ObjectRegistration* currentRegister = m_firstObject;

    while(currentRegister){
        currentRegister->object->getRigidbody2D()->zeroForce();

        currentRegister = currentRegister->next;
    }
}

void SceneOBB::generateContacts(){
    ObjectRegistration* hittee = m_firstObject;
    while(hittee){
        ObjectRegistration* hitter = hittee->next;
        while(hitter){
            if(!(hitter->object->getRigidbody2D()->hasInfiniteMass() && hittee->object->getRigidbody2D()->hasInfiniteMass())){
                if(Collision::isColliding(hittee->object->getBound(),hitter->object->getBound())){
                    std::cout << "Colliding " << ImGui::GetIO().DeltaTime<< std::endl;
                   
                    CollisionData generatedCol = Collision::calculateCollision(hittee->object->getBound(),hitter->object->getBound());

                    generatedCol.object[0] = hittee->object;
                    generatedCol.object[1] = hitter->object;

                    generatedCol.restitution = 0.0f;

                    testBoxCollision(hittee->object,hitter->object,&generatedCol);

                    Collision::resolve(ImGui::GetIO().DeltaTime,&generatedCol);
                        
                    m_collisionResolver->registerContact(generatedCol);
                }
            }
            hitter = hitter->next;
        }
        hittee = hittee->next;
    }
}

void SceneOBB::integrate(float dt){
    ObjectRegistration* currentRegister = m_firstObject;
    while(currentRegister){
        Physics2D::integrate(currentRegister->object,dt);
        currentRegister = currentRegister->next;
    }
}

void SceneOBB::runPhysics(float dt){
    //force generators
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

void SceneOBB::addObject(Object* newObject){
    if(!m_firstObject->object){
        m_firstObject->object = newObject;
    }else{
        ObjectRegistration* lastRegister = new ObjectRegistration();
        lastRegister->object = newObject;
        ObjectRegistration* currentRegistry = m_firstObject;
        while(currentRegistry->next){
            currentRegistry = currentRegistry->next;
        }
        currentRegistry->next = lastRegister;
    }
    m_numObjects++;
}

void SceneOBB::testBoxCollision(Object* obj1, Object* obj2, CollisionData* col){
    if(obj1->getRigidbody2D()->hasInfiniteMass()){
        Object* temp = obj2;
        obj2 = obj1;
        obj1 = temp;
    }

    if(col->distance.x / (obj1->getScaleXYZ().x * obj2->getScaleXYZ().x) > col->distance.y / (obj1->getScaleXYZ().y * obj2->getScaleXYZ().y)){
        if(obj1->getPositionXY().x > obj2->getPositionXY().x){
			col->collisionNormal.x = 1;
			col->collisionNormal.y = 0;
		}else{
			col->collisionNormal.x = -1;
			col->collisionNormal.y = 0;
		}
    }else{
        if(obj1->getPositionXY().y > obj2->getPositionXY().y){
			col->collisionNormal.x = 0;
			col->collisionNormal.y = 1;
		}else{
			col->collisionNormal.x = 0;
			col->collisionNormal.y = -1;
		}
    }
}
