#include "./SceneQuadTreeDemo.h"

SceneQuadTreeDemo::SceneQuadTreeDemo() :
    Scene("SceneQuadTreeDemo"),
    m_demo(new QuadTreeDemo(
        QuadTree(-1.0f, 1.0f, 2.0f, 2.0f)
    ))
{}


SceneQuadTreeDemo::~SceneQuadTreeDemo() {
    delete m_demo;
}

void SceneQuadTreeDemo::render(GWindow* window) {

    m_demo->show();
    //m_demo->m_quadTree.drawTree(true);

}

void SceneQuadTreeDemo::update(GWindow* window) {
    startFrame();
    runPhysics(ImGui::GetIO().DeltaTime);
    input(window);
}


void SceneQuadTreeDemo::renderGUI() {
    ImGui::Begin(m_title.c_str());
    ImGui::Text("Number of collision: %d", m_numCollisions);
    ImGui::End();
}

void SceneQuadTreeDemo::input(GWindow* window) {
    if (GInput::isMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
        float mouseX = 2.0f * (GInput::getMouseX() / window->getWidth()) - 1.0f;
        float mouseY = 2.0f * (-((GInput::getMouseY() / window->getHeight()) - 1.0f) - 0.5f);

        m_demo->m_quadTree.insertPoint(Point(mouseX, mouseY));
    }

}

void SceneQuadTreeDemo::checkBounds() {
    ObjectRegistration* currentRegistry = m_firstObject;
    while (currentRegistry) {
        Object* currentObject = currentRegistry->object;
        glm::vec2 pos = currentObject->getPosition();
        glm::vec2 vel = *(currentObject->getRigidbody2D()->getVelocity());
        if (pos.y < -300 || pos.y > 300) {
            currentObject->getRigidbody2D()->setVelocity(glm::vec2(vel.x, -vel.y));
            currentObject->setPosition(pos.x, pos.y - pos.y / 100.0f);
        }
        if (pos.x < -400 || pos.x > 400) {
            currentObject->getRigidbody2D()->setVelocity(glm::vec2(-vel.x, vel.y));
            currentObject->setPosition(pos.x - pos.x / 100.0f, pos.y);
        }

        currentRegistry = currentRegistry->next;
    }
}

void SceneQuadTreeDemo::runPhysics(float dt, GWindow* window) {
    ObjectRegistration* currentRegistry = m_firstObject;
    while (currentRegistry) {
        currentRegistry = currentRegistry->next;
    }

    integrate(ImGui::GetIO().DeltaTime);

    generateContacts();

    //checkBounds();
}