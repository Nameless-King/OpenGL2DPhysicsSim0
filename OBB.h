#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class OBB{
public:
    //m_center referenced from parent object
    glm::vec3* m_center;
    float m_rotation;
    glm::vec2* m_halfExtents;
    glm::vec2 m_localX;
    glm::vec2 m_localY;

    OBB();
    ~OBB();

    void setCenter(glm::vec3* center);
    void setHalfExtents(glm::vec2* halfExtents);

    inline glm::vec3* getCenter(){return m_center;}
    inline float getRotation() const {return m_rotation;}
    inline glm::vec2* getHalfExtents(){return m_halfExtents;}

    glm::vec3 getCenterXYZCopy();
    glm::vec2 getCenterXYCopy();
    glm::vec2 getHalfExtentsXYCopy();

};