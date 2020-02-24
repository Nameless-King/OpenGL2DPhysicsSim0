#include "./Experimental.h"

/*void Experimental::ExtremePointsAlongDirection(glm::vec2 dir, glm::vec3 points[], int n, int *imin, int* imax){
    float minproj = FLT_MAX;
    float maxproj = -FLT_MAX;

    for(int i = 0;i < n;i++){
        float proj = glm::dot(points[i],dir);

        if(proj < minproj){
            minproj = proj;
            *imin = i;
        }

        if(proj > maxproj){
            maxproj = proj;
            *imax = i;
        }
    }
}*/

void Experimental::UpdateAABB(Hitbox a, float rotZ,glm::vec2* temp){
   
}