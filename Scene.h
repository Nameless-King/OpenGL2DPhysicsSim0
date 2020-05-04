#pragma once

#include <iostream>
#include "./Window.h"

class Scene{
private:
	std::string m_title;
public:
	Scene();
	Scene(std::string title);
	~Scene();
	virtual void render(Window* window) = 0;
	virtual void update(Window* window) = 0;
	virtual std::string getSceneTitle()const = 0;
	virtual void renderGUI() = 0;
};