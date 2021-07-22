#include "./SceneCollisions.h"

static BoundingType type = BoundingType::Circle;
static float scale = 0.5f;

SceneCollisions::SceneCollisions():
    Scene("SceneCollisions"),
    m_useGravity(false),
    m_shader(NULL),
    m_texture(NULL),
    m_player(NULL),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f)))
{}

SceneCollisions::SceneCollisions(Shader* shader, Texture* texture):
    Scene("SceneCollisions"),
    m_shader(shader),
    m_texture(texture),
    m_useGravity(false),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,-1.0f * Physics2D::G)))
{

    m_player = new Object(
        glm::vec3(0.0f,0.0f,0.0f),
        0.0f,
        glm::vec3(scale,scale,scale)
    );
    m_player->createBound(type);
    m_player->addRigidbody2D(5.0f);

    addObject(m_player);

    const int winWidth = 800;
    const int winHeight = 600;
    const int numBalls = 100;
    for(int i = 0;i<numBalls;i++){
        int randX = -(winWidth/2) + (std::rand() % (winWidth + 1));
        int randY = -(winHeight/2) + (std::rand() % (winHeight + 1));
       
        Object* temp = new Object(
            glm::vec3(randX,randY,0.0f),
            0.0f,
            glm::vec3(scale,scale,scale)
        );
        temp->createBound(type);
        temp->addRigidbody2D(1.0f);

        addObject(temp);
    }

    m_forceGravity.setGravityType(GravityType::Point);
    m_forceGravity.setPoint(glm::vec2(0.0f,0.0f),10.0f);

}

SceneCollisions::~SceneCollisions(){
}

void SceneCollisions::render(GWindow* window){
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

void SceneCollisions::update(GWindow* window){
    startFrame();
    runPhysics(ImGui::GetIO().DeltaTime);
    input(window);
}


void SceneCollisions::renderGUI(){
    bool gravity = m_useGravity;
    ImGui::Begin(m_title.c_str());
    ImGui::Text("Number of collision: %d",m_numCollisions);
    if(ImGui::Checkbox("Use Gravity",&gravity)){
        m_useGravity = gravity;
    }
    if(ImGui::Button("Zero Velocity")){
        ObjectRegistration* currentRegistry = m_firstObject;
        while(currentRegistry){
            currentRegistry->object->getRigidbody2D()->setVelocity(0.0f,0.0f);
            currentRegistry = currentRegistry->next;
        }
    }
    ImGui::End();
}

void SceneCollisions::input(GWindow* window){
    //variables for force, position, and velocity
    //if wanted to change method of movement
    float px = m_player->getPositionXYZ().x;
    float py = m_player->getPositionXYZ().y;
    float vx = 0.0f;
    float vy = 0.0f;
    float speed = 1.0f;
    float velocity = 40.0f;

    glm::vec2 force(0.0f,0.0f);
    float fforce = 800.0f;

    if(GInput::isKeyDown(GLFW_KEY_UP)){
        py += speed;
        vy += velocity;
        force.y = fforce;
    }else if(GInput::isKeyDown(GLFW_KEY_DOWN)){
        py -= speed;
        vy -= velocity;
        force.y = -fforce;
    }

    if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
        px += speed;
        vx += velocity;
        force.x = fforce;
    }else if(GInput::isKeyDown(GLFW_KEY_LEFT)){
        px -= speed;
        vx -= velocity;
        force.x = -fforce;
    }

    //m_player->getRigidbody2D()->setVelocity(glm::vec2(vx,vy));
    m_player->getRigidbody2D()->addForce(force);
    //m_player->setPos(px,py);
}

void SceneCollisions::checkBounds(){
    ObjectRegistration* currentRegistry = m_firstObject;
    while(currentRegistry){
        Object* currentObject = currentRegistry->object;
        glm::vec2 pos = currentObject->getPositionXY();
        glm::vec2 vel = *(currentObject->getRigidbody2D()->getVelocity());
        if(pos.y < -300 || pos.y > 300){
            currentObject->getRigidbody2D()->setVelocity(glm::vec2(vel.x,-vel.y));
            currentObject->setPos(pos.x,pos.y - pos.y/100.0f);
        }
        if(pos.x < -400 || pos.x > 400){
            currentObject->getRigidbody2D()->setVelocity(glm::vec2(-vel.x,vel.y));
            currentObject->setPos(pos.x - pos.x/100.0f,pos.y);
        }

        currentRegistry = currentRegistry->next;
    }
}

void SceneCollisions::runPhysics(float dt, GWindow* window){
    ObjectRegistration* currentRegistry = m_firstObject;
    while(currentRegistry){
        if(m_useGravity){
            m_forceGravity.updateForce(currentRegistry->object,dt);
            //Physics2D::gravitate(glm::vec2(0.0f,0.0f),100.0f,currentRegistry->object);
        }
        currentRegistry = currentRegistry->next;
    }

    integrate(ImGui::GetIO().DeltaTime);

    generateContacts();

    checkBounds();
}