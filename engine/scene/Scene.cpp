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

std::string Scene::getSceneTitle() const {
    return m_title;
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
    return;
    ObjectRegistration* currentRegister = m_firstObject;
    while(currentRegister){
        //zeroing force is done in Physics 2d integrate
        //currentRegister->object->getRigidbody2D()->zeroForce();
        //currentRegister->object->getRigidbody2D()->setAngularVelocity(0.0f);
        currentRegister = currentRegister->next;
    }
}

void Scene::generateContacts(){
    ObjectRegistration* hittee = m_firstObject;
    while (hittee) {
        ObjectRegistration* hitter = hittee->next;
        while (hitter) {
            if (Collision::checkFlags(hittee->object,hitter->object) && Collision::boundingVolumeTest(hittee->object,hitter->object)) {
               
                if (Collision::isColliding(hittee->object->getBound(), hitter->object->getBound())) {
                        CollisionData generatedCol = Collision::calculateCollision(hittee->object, hitter->object);

                        Collision::resolve(ImGui::GetIO().DeltaTime, &generatedCol);

                        m_collisionResolver->registerContact(generatedCol);
                
                }
            }
            hitter = hitter->next;
        }
        hittee = hittee->next;
    }
    m_numCollisions = m_collisionResolver->numOfCollisions();
}