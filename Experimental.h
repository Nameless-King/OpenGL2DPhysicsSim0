#include <float.h>
#include <math.h>

#include "./Hitbox.h"


#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#define PI 3.14159


class Experimental{
public:
    //static void ExtremePointsAlongDirection(glm::vec2 dir, glm::vec3 points[], int n, int* imin, int* imax);

    static void UpdateAABB(Hitbox a, float rotZ,glm::vec2* temp);

};