#include "./SceneBuoyantForce.h"

SceneBuoyantForce::SceneBuoyantForce():
    m_title("SceneBuoyantForce"),
    m_active(false),
    m_shader(NULL),
    m_texture(NULL),
    m_object(NULL),
    m_forceBuoyancy(ForceBuoyancy()),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,0.0f))),
    m_forceDrag(ForceDrag(1.0f,1.0f)){}

SceneBuoyantForce::SceneBuoyantForce(Shader* shader, Texture* texture, const float vertices[]):
    m_title("SceneBuoyantForce"),
    m_active(false),
    m_shader(shader),
    m_texture(texture),
    m_forceGravity(ForceGravity(glm::vec2(0.0f,-15.0f))),
    m_forceDrag(ForceDrag(0.0f,0.05f)){
        m_object = new Object(
            glm::vec3(0.0f,10.0f,0.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(1.0f,1.0f,1.0f)
        );

        m_object->addVertices(vertices);
        m_object->createAABB(BBType::Circle);
        RigidBody2D* rb = new RigidBody2D(5.0f);
        rb->setDamping(1.0f);
        m_object->addRigidBody2D(rb);

        m_forceBuoyancy = ForceBuoyancy(-50.0f,1.0f,0,750.0f);

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
    m_forceGravity.updateForce(m_object,ImGui::GetIO().DeltaTime);
    m_forceBuoyancy.updateForce(m_object,ImGui::GetIO().DeltaTime);
    //m_forceDrag.updateForce(m_object,ImGui::GetIO().DeltaTime);

    Physics2D::integrator3(m_object,ImGui::GetIO().DeltaTime);
  
}

void SceneBuoyantForce::setActive(bool active){
    m_active = active;
}

void SceneBuoyantForce::renderGUI(){
    float gravity = m_forceGravity.getGravity().y;

    float maxDepth = m_forceBuoyancy.getMaxDepth();
    float volume = m_forceBuoyancy.getVolume();
    float waterHeight = m_forceBuoyancy.getWaterHeight();
    float liquidDensity = m_forceBuoyancy.getLiquidDensity();
    float k1 = m_forceDrag.getK1();

    ImGui::Begin(m_title.c_str());
    if(ImGui::DragFloat("Gravity",&gravity,0.5f)){
        m_forceGravity.setGravity(0.0f,gravity);
    }
    if(ImGui::DragFloat("K1",&k1,0.01f)){
        m_forceDrag.setK1(k1);
    }
    if(ImGui::DragFloat("Max Depth",&maxDepth,1.0f)){
        m_forceBuoyancy.setMaxDepth(maxDepth);
    }
    if(ImGui::DragFloat("Volume",&volume,0.5f)){
        m_forceBuoyancy.setVolume(volume);
    }
    if(ImGui::DragFloat("Water Height",&waterHeight,0.5f)){
        m_forceBuoyancy.setWaterHeight(waterHeight);
    }
    if(ImGui::DragFloat("Liquid Density",&liquidDensity,0.5f)){
        m_forceBuoyancy.setLiquidDensity(liquidDensity);
    }

    ImGui::End();
    
}

    