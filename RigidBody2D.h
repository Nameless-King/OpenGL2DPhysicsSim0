#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transformation.hpp"

class RigidBody2D(){
	glm::vec2* m_velocity;
	glm::vec2* m_acceleration;
	float m_damping; //0 to stop, 1 to never, 0.995 ok
	float m_mass;
	public:
		float getMass();
		float getInverseMass();

};
