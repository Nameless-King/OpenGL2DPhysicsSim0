
#include <vector>
#include <cstdlib>
#include <memory>

#include "../engine/graphics/Renderer.h"

struct Point{
    float x = 0;
    float y = 0;
    Point(): x(0),y(0){}
    Point(float px, float py):x(px),y(py){}
};


struct Rectangle{
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;
    Rectangle():x(0),y(0),w(0),h(0){}
    Rectangle(float px, float py, float pw, float ph):
        x(px),y(py),w(pw),h(ph){}
};

class QuadTree{
private:
    static int m_size;
    int m_capacity = 4;
public:
    //coordinate grid orientation
    QuadTree* m_quadrant1;
    QuadTree* m_quadrant2;
    QuadTree* m_quadrant3;
    QuadTree* m_quadrant4;

    Rectangle m_node;
    std::vector<Point> m_points;
    bool m_hasBranched;

    QuadTree();
    QuadTree(float originx, float originy, float w, float h);
    ~QuadTree(); 
    void insertPoint(Point point);
    void branchNode();
    bool insideThisNode(Point point);
    void drawPoints();
    void drawTree();

    
};


class QuadTreeDemo{
private:
    int m_maxPoints = 8;
    int m_subCapacity = 4;  
public:
    QuadTree m_quadTree;
    QuadTreeDemo();
    QuadTreeDemo( QuadTree m_quadTree);
    void show();
};