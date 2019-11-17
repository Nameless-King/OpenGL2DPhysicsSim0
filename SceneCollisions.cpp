#include "./SceneCollisions.h"

SceneCollisions::SceneCollisions():
    m_title("SceneCollisions"),
    m_active(false),
    m_shader(NULL),
    m_texture(NULL),
    m_player(NULL),
    m_other(NULL),
    m_contactResolver(ObjectContact())
{}

SceneCollisions::SceneCollisions(Shader* shader, Texture* texture, const float vertices[]):\
    m_title("SceneCollisions"),
    m_shader(shader),
    m_texture(texture),
    m_active(false),
    m_contactResolver(ObjectContact())
{
    m_player = new Object(
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(1.0f,1.0f,1.0f)
    );
    m_player->addVertices(vertices);
    m_player->createAABB(BBType::Circle);

    RigidBody2D* rbPlayer = new RigidBody2D(5.0f);
    m_player->addRigidBody2D(rbPlayer);

    m_other = new Object(
        glm::vec3(0.0f,20.0f,0.0f),
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(1.0f,1.0f,1.0f)
    );
    m_other->addVertices(vertices);
    m_other->createAABB(BBType::Circle);

    RigidBody2D* rbOther = new RigidBody2D(5.0f);
    m_other->addRigidBody2D(rbOther);
}

SceneCollisions::~SceneCollisions(){
    delete m_player;
    delete m_other;
}

std::string SceneCollisions::getSceneTitle() const {
    return m_title;
}

bool SceneCollisions::isActive() const{
    return m_active;
}

void SceneCollisions::render(Window* window){
    StaticRenderer::bind();

    m_shader->use();
    m_texture->bind();

    m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
    m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));

    m_shader->setUniformMat4f("u_model",m_player->getModelMatrix());
    StaticRenderer::renderObject();

    m_shader->setUniformMat4f("u_model",m_other->getModelMatrix());
    StaticRenderer::renderObject();

    m_texture->unbind();

    StaticRenderer::unbind();
}

void SceneCollisions::update(Window* window){
    input(window);

    Physics2D::integrator3(m_player,ImGui::GetIO().DeltaTime);

    Collision objCol = AABB::getCollision(m_player->getBoundingBox(),m_other->getBoundingBox());

    if(objCol.colliding){
        m_contactResolver.object[0] = m_other;
        m_contactResolver.object[1] = m_player;
        m_contactResolver.m_restitution = 1.0f;
        m_contactResolver.m_contactNormal = objCol.collisionNormal;

        m_contactResolver.resolve(ImGui::GetIO().DeltaTime);

        Physics2D::updatePos(m_other,ImGui::GetIO().DeltaTime);
        Physics2D::updatePos(m_player,ImGui::GetIO().DeltaTime);
    }
}

void SceneCollisions::renderGUI(){
    ImGui::Begin(m_title.c_str());
    ImGui::End();
}

void SceneCollisions::setActive(bool active){
    m_active = active;
}

void SceneCollisions::input(Window* window){
    float px = m_player->getPos().x;
    float py = m_player->getPos().y;
    float speed = 1.0f;

    glm::vec2 force(0.0f,0.0f);
    float fforce = 50.0f;

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