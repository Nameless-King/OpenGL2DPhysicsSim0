#pragma once

#include "./Window.h"

class Scene{
public:
	virtual void render(Window* window);
	virtual void update(Window* window);
	virtual void renderGUI();
	virtual std::string getSceneTitle();
	virtual bool isActive();
	virtual void setActive(bool active);
};