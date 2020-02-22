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
    glm::mat3 m(1.0f);
    m[0][0] = cos((PI/180)*rotZ);
    m[0][1] = -sin((PI/180)*rotZ);
    m[1][0] = sin((PI/180)*rotZ);
    m[1][1] = cos((PI/180)*rotZ);

    float extents[2];
    
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            //(b.getCenter())* += m[i][j] * (a.getCenter())*;
            extents[i] += abs(m[i][j]) * (a.getHalfExtents()[j]);
        }   
    }
    (*temp)[0] = extents[0];
    (*temp)[1] = extents[1];
    
}