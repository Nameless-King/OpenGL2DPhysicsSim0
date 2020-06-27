#include "./SceneTest.h"

SceneTest::SceneTest():
    Scene("SceneTest"),
    m_shader(NULL),
    m_texture(NULL),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * 1.0f))),
    m_playerSpeed(100.0f){
    }

SceneTest::SceneTest(Shader* shader, Texture* texture):
    Scene("SceneTest"),
    m_shader(shader),
    m_texture(texture),
    m_maxContacts(0),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,Physics2D::G * -10.0f))),
    m_playerSpeed(100.0f){

        Object* player = new Object(
            glm::vec3(0.0f,10.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );
        //player->addVertices(vertices);
        player->createBound(BoundingType::AxisAligned);
        player->addRigidbody2D(new Rigidbody2D(1.0f));


        addObject(player);
        m_player = player;

        Object* floor = new Object(
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(30.0f,1.0f,1.0f)
        );
        floor->createBound(BoundingType::AxisAligned);
        floor->addRigidbody2D(new Rigidbody2D(-1.0f));

        addObject(floor);
    }

SceneTest::~SceneTest(){
}

void SceneTest::render(GWindow* window){
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

void SceneTest::update(GWindow* window){
    startFrame();
    runPhysics(ImGui::GetIO().DeltaTime);
    input(window);
}

void SceneTest::renderGUI(){
    ImGui::Begin(getSceneTitle().c_str());
    ImGui::Text("Number of collision: %d",m_numCollisions);
    ImGui::Text("Number of objects: %d",m_numObjects);
    int playerSpeed = (int)m_playerSpeed;
    if(ImGui::SliderInt("Player Speed",&playerSpeed,1,200)){
		m_playerSpeed = (float)playerSpeed;
	}
    ImGui::End();
}

void SceneTest::input(GWindow* window){
    glm::vec2* playerVel = m_player->getRigidbody2D()->getVelocity();
    float speed = m_playerSpeed;

    if(GInput::isKeyDown(GLFW_KEY_UP)){
        playerVel->y = speed;
    }else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
        playerVel->y = -speed;
    }

    if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
        playerVel->x = speed;
    }else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
        playerVel->x = -speed;
    }

    //creates infinite mass objects upon left click at mouse position
    if(GInput::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)){
        glm::vec2 mousePos = GInput::getMouseXY();

        window->projectCoords(&mousePos);

        Object* newObject = new Object(
            glm::vec3(mousePos.x,mousePos.y,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );
        newObject->createBound(BoundingType::AxisAligned);
        newObject->addRigidbody2D(new Rigidbody2D(-1.0f));

        addObject(newObject);
    }

    //creates finite mass objects upon right click at mouse position
    if(GInput::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)){
        glm::vec2 mousePos = GInput::getMouseXY();

        window->projectCoords(&mousePos);

        Object* newObject = new Object(
            glm::vec3(mousePos.x,mousePos.y,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );
        newObject->createBound(BoundingType::AxisAligned);
        newObject->addRigidbody2D(new Rigidbody2D(1.0f));

        addObject(newObject);

    }
}

void SceneTest::runPhysics(float dt){
    //force generators
    ObjectRegistration* currentRegister = m_firstObject;
    while(currentRegister){
        m_forceGravity.updateForce(currentRegister->object,ImGui::GetIO().DeltaTime);
        currentRegister = currentRegister->next;
    }
    
    integrate(ImGui::GetIO().DeltaTime);
   
    generateContacts();
    //m_collisionResolver->resolveContacts(ImGui::GetIO().DeltaTime);
}

