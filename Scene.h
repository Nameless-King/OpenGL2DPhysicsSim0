#pragma once

#include <iostream>
#include "./Window.h"

class Scene{
public:
	~Scene(){};
	virtual void render(Window* window) = 0;
	virtual void update(Window* window) = 0;
	virtual std::string getSceneTitle()const = 0;
	virtual bool isActive()const = 0;
	virtual void setActive(bool active) = 0;
	virtual void renderGUI() = 0;
};