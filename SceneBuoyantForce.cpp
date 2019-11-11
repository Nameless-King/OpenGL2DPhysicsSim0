#include "./SceneBuoyantForce.h"

SceneBuoyantForce::SceneBuoyantForce():
    m_title("SceneBuoyantForce"),
    m_active(false),
    m_shader(NULL),
    m_texture(NULL),
    m_object(NULL){}

SceneBuoyantForce::SceneBuoyantForce(Shader* shader, Texture* texture, const float vertices[]):
    m_title("SceneBuoyantForce"),
    m_active(false),
    m_shader(shader),
    m_texture(texture){
        m_object = new Object(
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );

        m_object->addVertices(vertices);
        m_object->createAABB(BBType::Circle);
        RigidBody2D* rb = new RigidBody2D(5.0f);
        rb->setDamping(1.0f);
        m_object->addRigidBody2D(rb);
        
}

SceneBuoyantForce::~SceneBuoyantForce(){
    delete m_object;
}

std::string SceneBuoyantForce::getSceneTitle() const{
      return m_title;
}

bool SceneBuoyantForce::isActive()const{
     return m_active;
}

void SceneBuoyantForce::render(Window* window){
    StaticRenderer::bind();

    m_shader->use();
    m_texture->bind();

    m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
    m_shader->setUniformMat4f("u_view",glm::mat4(1.0f));

    m_shader->setUniformMat4f("u_model",m_object->getModelMatrix());
    StaticRenderer::renderObject();

    m_texture->unbind();

    StaticRenderer::unbind();
}

void SceneBuoyantForce::update(Window* window){

}

void SceneBuoyantForce::setActive(bool active){
    m_active = active;
}

void SceneBuoyantForce::renderGUI(){
    ImGui::Begin(m_title.c_str());
    ImGui::End();
}

    