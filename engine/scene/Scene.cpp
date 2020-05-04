#include "./Scene.h"

Scene::Scene(const std::string& title)
    :m_title(title){

}

std::string Scene::getSceneTitle() const {
    return m_title;
}