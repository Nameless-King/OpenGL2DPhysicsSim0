#pragma once

class Scene{
public:
	virtual void render() = 0;
	virtual std::string getSceneTitle() = 0;
	virtual bool isActive() = 0;
	virtual bool setActive() = 0;
};