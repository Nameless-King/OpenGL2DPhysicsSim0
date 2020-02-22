#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class OBB{
public:
    //m_center referenced from parent object
    glm::vec3* m_center;
    glm::mat3* m_orientation;
    glm::vec2* m_halfExtents;

    OBB();
    ~OBB();


    inline glm::vec3* getCenter(){return m_center;}
    inline glm::mat3* getOrientation(){return m_orientation;}
    inline glm::vec2* getHalfExtents(){return m_halfExtents;}

    glm::vec3 getCenterXYZCopy();
    glm::vec2 getHalfExtentsXYCopy();

};