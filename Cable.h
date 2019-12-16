#include "./Object.h"
#include "./ObjectContact.h"

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

class Cable{
    public:
        Object* m_objects[2];
        float m_maxLength;
        float m_restitution;
    public:
        unsigned int fillContact(ObjectContact* contact, unsigned int limit) const;
        float currentLength() const;
}