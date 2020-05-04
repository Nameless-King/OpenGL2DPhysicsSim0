#pragma once

#include <iostream>
#include "../io/GWindow.h"

class Scene{
public:
    std::string m_title;
    Scene(const std::string& title);
    ~Scene(){};
    virtual void render(GWindow* window) = 0;
    virtual void update(GWindow* window) = 0;
    std::string getSceneTitle() const; 
    virtual void renderGUI() = 0;
};