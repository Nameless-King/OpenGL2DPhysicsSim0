#include "./SceneOBB.h"

SceneOBB::SceneOBB() :
    Scene("SceneOBB"),
    m_shader(NULL),
    m_texture(NULL),
    m_forceGravity(ForceGravity(glm::vec2(0.0f, Physics2D::G * 0.0f))),
    m_collisionResolver(new CollisionBatchResolver(1)),
    m_maxContacts(0),
    m_player(0),
    m_test(0) {
}

SceneOBB::SceneOBB(Shader* shader, Texture* texture) :
    Scene("SceneOBB"),
    m_shader(shader),
    m_texture(texture),
    m_maxContacts(0),
    m_forceGravity(ForceGravity(glm::vec2(0.0f, Physics2D::G * 0.0f))),
    m_collisionResolver(new CollisionBatchResolver(1)){

    Object* player = new Object(
        glm::vec3(0.0f, 10.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    player->createBound(BoundingType::Oriented);
    player->addRigidbody2D(new Rigidbody2D(5.0f));
    addObject(player);
    m_player = player;

    Object* testBlock = new Object(
        glm::vec3(0.0f, -10.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    testBlock->createBound(BoundingType::Oriented);
    testBlock->addRigidbody2D(new Rigidbody2D(-1.0f));
    addObject(testBlock);
    m_test = testBlock;

    //testBlock = new Object(
    //    glm::vec3(0.0f,-50.0f,0.0f),
    //    glm::vec3(0.0f,0.0f,0.0f),
    //    glm::vec3(2.0f,1.0f,1.0f)
    //);
    //testBlock->createBound(BoundingType::Oriented);
    //testBlock->addRigidbody2D(new Rigidbody2D(-1.0f));
    //addObject(testBlock);


}

SceneOBB::~SceneOBB() {
    ObjectRegistration* currentRegistry = m_firstObject;
    ObjectRegistration* temp = NULL;
    while (currentRegistry) {
        delete currentRegistry->object;
        temp = currentRegistry;
        currentRegistry = currentRegistry->next;
        delete temp;
    }
    delete m_collisionResolver;
}

void SceneOBB::render(GWindow* window) {
    Renderer::bind();
    m_shader->use();
    m_texture->bind();
    m_shader->setUniformMat4f("u_projection", window->getProjectionMatrix());
    m_shader->setUniformMat4f("u_view", window->getCamera()->getViewMatrix());

    ObjectRegistration* currentRegistry = m_firstObject;
    while (currentRegistry) {
        m_shader->setUniformMat4f("u_model", currentRegistry->object->getModelMatrix());
        Renderer::renderObject();
        currentRegistry = currentRegistry->next;
    }
    m_texture->unbind();
    Renderer::unbind();
}

void SceneOBB::update(GWindow* window) {
    runPhysics(ImGui::GetIO().DeltaTime);
    input(window);
}

void SceneOBB::renderGUI() {
    ImGui::Begin(getSceneTitle().c_str());
    ImGui::Text("Number of collision: %d", m_numCollisions);
    ImGui::Text("Number of objects: %d", m_numObjects);
    ImGui::End();
}

void SceneOBB::input(GWindow* window) {
    glm::vec2 velocity(0.0f, 0.0f);
    float speed = 10.0f;

    if (GInput::isKeyDown(GLFW_KEY_UP)) {
        velocity.y = speed;
        m_player->m_transformationChanged = true;
    }
    else if (GInput::isKeyDown(GLFW_KEY_DOWN)) {
        velocity.y = -speed;
        m_player->m_transformationChanged = true;
    }

    if (GInput::isKeyDown(GLFW_KEY_RIGHT)) {
        velocity.x = speed;
        m_player->m_transformationChanged = true;
    }
    else if (GInput::isKeyDown(GLFW_KEY_LEFT)) {
        velocity.x = -speed;
        m_player->m_transformationChanged = true;
    }

    m_player->getRigidbody2D()->setVelocity(velocity);

    if (GInput::isKeyDown(GLFW_KEY_R)) {
        m_player->rotateDegrees(0.5f);
    }

    if (GInput::isKeyDown(GLFW_KEY_C)) {
        m_test->rotateDegrees(0.5f);
    }
}



void SceneOBB::generateContacts() {
    ObjectRegistration* hittee = m_firstObject;
    while (hittee) {
        ObjectRegistration* hitter = hittee->next;
        while (hitter) {
            if (!(hitter->object->getRigidbody2D()->hasInfiniteMass() && hittee->object->getRigidbody2D()->hasInfiniteMass())) {
               
                if (hittee->object->getBound()->getBoundingType() != BoundingType::Oriented &&
                Collision::isColliding(hittee->object->getBound(), hitter->object->getBound())) {
                        CollisionData generatedCol = Collision::calculateCollision(hittee->object->getBound(), hitter->object->getBound());

                        generatedCol.object[0] = hittee->object;
                        generatedCol.object[1] = hitter->object;

                        generatedCol.restitution = 0.0f;

                        Collision::calculateAABBNormals(&generatedCol);

                        Collision::resolve(ImGui::GetIO().DeltaTime, &generatedCol);
                        m_collisionResolver->registerContact(generatedCol);
                }else{ 
                    std::vector<glm::vec2> verts;
                    if (Collision::GJKTest(hittee->object, hitter->object, &verts)) {
                        //need to make sure no undefined behavior is occuring in EPATest
                        glm::vec2 penetrationVector = Collision::EPATest(verts);

                        CollisionData generatedCol;

                        generatedCol.distance = *(hitter->object->getBound()->getCenter()) - *(hittee->object->getBound()->getCenter());
                        //generatedCol.distance.x = fabs(generatedCol.distance.x);
                        //generatedCol.distance.y = fabs(generatedCol.distance.y);


                        generatedCol.penetrationDepth = penetrationVector;
                        if (penetrationVector.x == penetrationVector.y && penetrationVector.x < 0.00001f) {
                            break;
                        }

                        generatedCol.collisionNormal = glm::normalize(penetrationVector);

                        generatedCol.object[0] = hittee->object;
                        generatedCol.object[1] = hitter->object;

                        Collision::resolve(ImGui::GetIO().DeltaTime, &generatedCol);
                        m_collisionResolver->registerContact(generatedCol);
                    }
                }
            }
            hitter = hitter->next;
        }
        hittee = hittee->next;
    }
}



void SceneOBB::runPhysics(float dt) {
    //force generators
    ObjectRegistration* currentRegister = m_firstObject;
    while (currentRegister) {
        m_forceGravity.updateForce(currentRegister->object, ImGui::GetIO().DeltaTime);
        currentRegister = currentRegister->next;
    }

    integrate(ImGui::GetIO().DeltaTime);

    generateContacts();

    m_numCollisions = m_collisionResolver->numOfCollisions();
    m_collisionResolver->resetRegistry();
}
