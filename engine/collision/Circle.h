#include "./Bound.h"


class Circle : public Bound{
public:
    Circle(): Bound() {}
    Circle(const Circle& bound): Bound(bound){}
    Circle(glm::vec3* center, glm::vec3* scale, const float* pvertices):Bound(center,scale,pvertices,BoundingType::AxisAligned){}
};