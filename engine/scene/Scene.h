#pragma once

#include <GL/glew.h>

#include <iostream>
#include "../physics/Physics2D.h"
#include "../collision/Collision.h"
#include "../collision/CollisionBatchResolver.h"
#include "../io/GWindow.h"
#include "../Object.h"

class Scene{
protected:
    struct ObjectRegistration{
        Object* object;
        ObjectRegistration* next;
    };
    unsigned int m_numObjects;
    unsigned int m_numCollisions;
    ObjectRegistration* m_firstObject;
    CollisionBatchResolver* m_collisionResolver;


public:
    std::string m_title;
    Scene();
    Scene(const std::string& title);
    ~Scene();
    virtual void render(GWindow* window) = 0;
    virtual void update(GWindow* window) = 0;
    virtual void renderGUI() = 0;
    std::string getSceneTitle() const; 
    
protected:
    virtual void input(GWindow* window) = 0;
    void addObject(Object* newObject);
    void integrate(float dt);
    void startFrame();
    void generateContacts();
    
};