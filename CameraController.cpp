#include "./CameraController.h"

CameraController::CameraController():
    m_viewMatrix(glm::mat4(1.0f)),
    m_cameraPos(glm::vec2(0.0f,0.0f)),
    m_zoom(2.0f)
{}

CameraController::CameraController(glm::vec2 pos):
    m_viewMatrix(glm::mat4(1.0f)),
    m_cameraPos(glm::vec2(pos)),
    m_zoom(2.0f)
{}

CameraController::~CameraController(){}

glm::mat4 CameraController::getViewMatrix(){
    m_viewMatrix = glm::lookAt(glm::vec3(m_cameraPos.x,m_cameraPos.y,0.0f),glm::vec3(m_cameraPos.x,m_cameraPos.y,0.0f)+glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,1.0f,0.0f));
    return m_viewMatrix;
}

void CameraController::setCameraPos(float px, float py){
    m_cameraPos.x = px;
    m_cameraPos.y = py;
}

void CameraController::setCameraPos(glm::vec2 pos){
    m_cameraPos = glm::vec2(pos);
}

void CameraController::setCameraZoom(float zoom){
    m_zoom = zoom;
}

glm::vec2 CameraController::getCameraPos(){
    return m_cameraPos;
}

float CameraController::getCameraZoom(){
    return m_zoom;
}