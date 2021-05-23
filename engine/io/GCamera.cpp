#include "./GCamera.h"

GCamera::GCamera():
    m_viewMatrix(glm::mat4(1.0f)),
    m_cameraPos(glm::vec2(0.0f,0.0f)),
    m_zoom(2.0f)
{}

GCamera::GCamera(glm::vec2 pos):
    m_viewMatrix(glm::mat4(1.0f)),
    m_cameraPos(glm::vec2(pos)),
    m_zoom(2.0f)
{}

GCamera::~GCamera(){}

glm::mat4 GCamera::getViewMatrix(){
    m_viewMatrix = glm::lookAt(glm::vec3(m_cameraPos.x,m_cameraPos.y,0.0f),glm::vec3(m_cameraPos.x,m_cameraPos.y,0.0f)+glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,1.0f,0.0f));
    return m_viewMatrix;
}

void GCamera::setCameraPos(float px, float py){
    m_cameraPos.x = px;
    m_cameraPos.y = py;
}

void GCamera::setCameraPos(glm::vec2 pos){
    m_cameraPos = glm::vec2(pos);
}

void GCamera::setCameraZoom(float zoom){
    m_zoom = zoom;
}

void GCamera::addCameraPosOffset(float px, float py){
    m_cameraPos.x += px;
    m_cameraPos.y += py;
}

void GCamera::addCameraZoomOffset(float zoom){
    std::cout << m_zoom << " " << zoom << " " << m_zoom + zoom << std::endl;
    m_zoom += zoom;
}

glm::vec2 GCamera::getCameraPos(){
    return m_cameraPos;
}

float GCamera::getCameraZoom(){
    return m_zoom;
}

