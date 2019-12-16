
#include "./Object.h"
#include "./ObjectContact.h"

#include "./Dependencies/glm/glm.hpp" 
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class Rods{
    public:
        Object* m_objects[2];
        float m_length;
    public:
        float currentLength() const;
        unsigned int fillContact(ObjectContact* contact, unsigned int limit) const;
};