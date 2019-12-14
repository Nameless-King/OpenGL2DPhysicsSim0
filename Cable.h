#include "./Object.h"
#include "./ObjectContact.h"

class Cable{
    public:
        Object* m_objects[2];
        float m_maxLength;
        float m_restitution;
    
    private:
        float currentLength() const;

    public:
        unsigned int fillContact(ObjectContact* contact, unsigned int limit) const;
}