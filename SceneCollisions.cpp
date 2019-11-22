#include "./SceneCollisions.h"

static bool hasCollided = false;
static BBType type = BBType::AxisAligned;

SceneCollisions::SceneCollisions():
    m_title("SceneCollisions"),
    m_useGravity(false),
    m_shader(NULL),
    m_texture(NULL),
    m_player(NULL),
    m_contactResolver(ObjectContact()),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f)))
{}

SceneCollisions::SceneCollisions(Shader* shader, Texture* texture, const float vertices[]):
    m_title("SceneCollisions"),
    m_shader(shader),
    m_texture(texture),
    m_useGravity(false),
    m_contactResolver(ObjectContact()),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,-5.0f * Physics2D::G)))
{

    m_player = new Object(
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(1.0f,1.0f,1.0f)
    );
    m_player->addVertices(vertices);
    m_player->createAABB(type);

    RigidBody2D* rbPlayer = new RigidBody2D(5.0f);
    m_player->addRigidBody2D(rbPlayer);


    for(int i = 0;i<5;i++){
        float x_pos = (i+1) * (395.0f/5.0f);
        m_objects.push_back(new Object(
            glm::vec3(x_pos,295.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        ));
        m_objects[i]->addVertices(vertices);
        m_objects[i]->createAABB(type);
        m_objects[i]->addRigidBody2D(new RigidBody2D(5.0f));
    }

    for(int i = 5;i<10;i++){
        float x_pos = ((i-5)+1) * (397.0f/5.0f);
        m_objects.push_back(new Object(
            glm::vec3(x_pos,-295.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        ));
        m_objects[i]->addVertices(vertices);
        m_objects[i]->createAABB(type);
        m_objects[i]->addRigidBody2D(new RigidBody2D(5.0f));
    }


}

SceneCollisions::~SceneCollisions(){
    delete m_player;
    for(int i = 0;i<m_objects.size();i++){
        delete m_objects[i];
    }
}

std::string SceneCollisions::getSceneTitle() const {
    return m_title;
}

void SceneCollisions::render(Window* window){
    StaticRenderer::bind();

    m_shader->use();
    m_texture->bind();

    m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
    m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));

    m_shader->setUniformMat4f("u_model",m_player->getModelMatrix());
    StaticRenderer::renderObject();

    for(int i = 0;i<m_objects.size();i++){
        m_shader->setUniformMat4f("u_model",m_objects[i]->getModelMatrix());
        StaticRenderer::renderObject();

    }

    m_texture->unbind();

    StaticRenderer::unbind();
}

void SceneCollisions::update(Window* window){
    input(window);

    if(m_useGravity){
        m_forceGravity.updateForce(m_player,ImGui::GetIO().DeltaTime);
        for(int i = 0;i<m_objects.size();i++){
            m_forceGravity.updateForce(m_objects[i],ImGui::GetIO().DeltaTime);
        }
    }

    Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);
    for(int i = 0;i<m_objects.size();i++){
        if(!hasCollided){
                if(i<5){
                    m_objects[i]->getRigidBody2D()->addForce(glm::vec2(0.0f,-50.0f));
                }else{
                    m_objects[i]->getRigidBody2D()->addForce(glm::vec2(0.0f,50.0f));
                }
        }
        
        Physics2D::integrator3(m_objects[i],ImGui::GetIO().DeltaTime);
    }
    
    float restitution = 0.0f;
    for(int i = 0;i<m_objects.size();i++){
        Collision playerCol = AABB::getCollision(m_player->getBoundingBox(),m_objects[i]->getBoundingBox());

        

        if(playerCol.colliding){
            m_contactResolver.object[0] = m_objects[i];
            m_contactResolver.object[1] = m_player;
            m_contactResolver.m_restitution = restitution;
            m_contactResolver.m_contactNormal = playerCol.collisionNormal;
            m_contactResolver.resolve(ImGui::GetIO().DeltaTime,playerCol);
        }
    }

    for(int i = 0;i<m_objects.size();i++){
        for(int j = i+1;j<m_objects.size();j++){
            Collision objectCol = AABB::getCollision(m_objects[i]->getBoundingBox(),m_objects[j]->getBoundingBox());

            

            if(objectCol.colliding){
                hasCollided = true;
                m_contactResolver.object[0] = m_objects[j];
                m_contactResolver.object[1] = m_objects[i];
                m_contactResolver.m_restitution = restitution;
                m_contactResolver.m_contactNormal = objectCol.collisionNormal;
                m_contactResolver.resolve(ImGui::GetIO().DeltaTime,objectCol);
            }
        }
    }

    checkBounds();

}


void SceneCollisions::renderGUI(){
    bool gravity = m_useGravity;
    ImGui::Begin(m_title.c_str());
    if(ImGui::Checkbox("Use Gravity",&gravity)){
        m_useGravity = gravity;
    }
    ImGui::End();
}

void SceneCollisions::input(Window* window){
    float px = m_player->getPos().x;
    float py = m_player->getPos().y;
    float speed = 1.0f;

    glm::vec2 force(0.0f,0.0f);
    float fforce = 150.0f;

    if(glfwGetKey(window->getWindow(),GLFW_KEY_W)){
        py += speed;
        force.y = fforce;
    }else if(glfwGetKey(window->getWindow(),GLFW_KEY_S)){
        py -= speed;
        force.y = -fforce;
    }

    if(glfwGetKey(window->getWindow(),GLFW_KEY_D)){
        px += speed;
        force.x = fforce;
    }else if(glfwGetKey(window->getWindow(),GLFW_KEY_A)){
        px -= speed;
        force.x = -fforce;
    }

    m_player->getRigidBody2D()->addForce(force);
    //m_player->setPos(px,py);
}

void SceneCollisions::checkBounds(){
    for(int i = 0;i<m_objects.size();i++){
        glm::vec2 pos = m_objects[i]->getPos2();
        glm::vec2 vel = *(m_objects[i]->getRigidBody2D()->getVelocity());
        if(pos.y < -300 || pos.y > 300){
            m_objects[i]->getRigidBody2D()->setVelocity(glm::vec2(vel.x,-vel.y));
            m_objects[i]->setPos(pos.x,pos.y - pos.y/100.0f);
        }
        if(pos.x < -400 || pos.x > 400){
            m_objects[i]->getRigidBody2D()->setVelocity(glm::vec2(-vel.x,vel.y));
            m_objects[i]->setPos(pos.x - pos.x/100.0f,pos.y);
        }
    }

    glm::vec2 pos = m_player->getPos2();
    glm::vec2 vel = *(m_player->getRigidBody2D()->getVelocity());
    if(pos.y<-300 || pos.y >300){
        m_player->getRigidBody2D()->setVelocity(glm::vec2(vel.x,-vel.y));
        m_player->setPos(pos.x,pos.y - pos.y/100.0f);
    }
    if(pos.x < -400 || pos.x > 400){
        m_player->getRigidBody2D()->setVelocity(glm::vec2(-vel.x,vel.y));
        m_player->setPos(pos.x - pos.x/100.0f,pos.y);
    }
}
