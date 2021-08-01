#include "./Bound.h"


class Circle : public Bound{
public:
    Circle(): Bound() {}
    Circle(const Circle& bound): Bound(bound){}
    Circle(glm::vec2* center, float* rotation, glm::vec2* scale, const float* pvertices,int vertexCount):Bound(center,rotation,scale,pvertices,vertexCount,BoundingType::AxisAligned){}
};