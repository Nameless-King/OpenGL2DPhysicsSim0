#include "./Scene.h"

Scene::Scene():
    m_title("Default Title"),
    m_numCollisions(0),
    m_numObjects(0),
    m_firstObject(new ObjectRegistration()),
    m_collisionResolver(new CollisionBatchResolver(1)){}

Scene::Scene(const std::string& title)
    :m_title(title),
    m_numCollisions(0),
    m_numObjects(0),
    m_firstObject(new ObjectRegistration()),
    m_collisionResolver(new CollisionBatchResolver(1)){}

Scene::~Scene(){
    m_collisionResolver->resetRegistry();
    delete m_collisionResolver;

    ObjectRegistration* currentRegistry = m_firstObject;
    ObjectRegistration* temp = NULL;
    while(currentRegistry){
        if(currentRegistry->object){
            delete currentRegistry->object;
        }
        temp = currentRegistry;
        currentRegistry = currentRegistry->next;
        delete temp;
    }

}

void Scene::addObject(Object* newObject){
    if(!m_firstObject->object){
        m_firstObject->object = newObject;
    }else{
        ObjectRegistration* lastRegister = new ObjectRegistration();
        lastRegister->object = newObject;
        ObjectRegistration* currentRegistry = m_firstObject;
        while(currentRegistry->next){
            currentRegistry = currentRegistry->next;
        }
        currentRegistry->next = lastRegister;
    }
    m_numObjects++;
}

void Scene::integrate(float dt) {
    ObjectRegistration* currentRegister = m_firstObject;
    while (currentRegister) {
        Physics2D::integrate(currentRegister->object, dt);
        currentRegister = currentRegister->next;
    }
}

void Scene::startFrame(){
    m_collisionResolver->resetRegistry();

    ObjectRegistration* currentRegister = m_firstObject;
    while(currentRegister){
        currentRegister->object->getRigidbody2D()->zeroForce();
        //currentRegister->object->getRigidbody2D()->setAngularVelocity(0.0f);
        currentRegister = currentRegister->next;
    }
}

std::string Scene::getSceneTitle() const {
    return m_title;
}