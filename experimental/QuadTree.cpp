#include "./QuadTree.h"

int QuadTree::m_size = 0;

QuadTree::QuadTree() :m_hasBranched(false) {}

QuadTree::QuadTree(float originx, float originy, float w, float h) :
    m_node(Rectangle(originx, originy, w, h)),
    m_hasBranched(false) {
    m_size += 1;
}

QuadTree::~QuadTree() {
    // delete m_quadrant1;
    // delete m_quadrant2;
    // delete m_quadrant3;
    // delete m_quadrant4;
}

void QuadTree::insertPoint(Point point) {
    if (!insideThisNode(point)) {
        return;
    }

    if (m_points.size() < m_capacity) {
        m_points.push_back(point);
    }
    else {
        //only branch nodes once which will init all quadrant variables
        //NOTE A NEWLY CREATED POINT ISN'T GUARENTEED THE VALUE OF ZERO
        //ALSO NOTE EACH COMPILER CAN BE DIFFERENT
        //JUST CAUSE IT WORKS ON ONE COMPILER DOESN'T MEAN IT WOULD WORK ON ANOTHER
        if (!m_hasBranched) {
            branchNode();
        }

        //insertPoint is recursive
        m_quadrant1->insertPoint(point);
        m_quadrant2->insertPoint(point);
        m_quadrant3->insertPoint(point);
        m_quadrant4->insertPoint(point);

    }
}

void QuadTree::branchNode() {
    m_hasBranched = true;
    float branchWidth = m_node.w / 2.0f;
    float branchHeight = m_node.h / 2.0f;
    m_quadrant1 = new QuadTree(m_node.x + branchWidth, m_node.y, branchWidth, branchHeight);
    m_quadrant2 = new QuadTree(m_node.x, m_node.y, branchWidth, branchHeight);
    m_quadrant3 = new QuadTree(m_node.x, m_node.y - branchHeight, branchWidth, branchHeight);
    m_quadrant4 = new QuadTree(m_node.x + branchWidth, m_node.y - branchHeight, branchWidth, branchHeight);
}

bool QuadTree::insideThisNode(Point point) {
    bool boolean = (m_node.x < point.x&& m_node.x + m_node.w >= point.x)
        && (m_node.y > point.y && m_node.y - m_node.h <= point.y);
    return boolean;
}

void QuadTree::drawPoints(){
    //draw points
    for (int i = 0; i < m_points.size(); i++) {
        Renderer::basicRenderPoint(m_points[i].x, m_points[i].y);
    }

    if (m_hasBranched) {
        m_quadrant1->drawPoints();
        m_quadrant2->drawPoints();
        m_quadrant3->drawPoints();
        m_quadrant4->drawPoints();
    }
}

void QuadTree::drawTree() {
    //draw main rect node
    //not very optimized 
    //has to build a vertex buffer and vertex array for each basicRenderEnd (draw call)
    // Renderer::basicRenderBegin(BasicRenderMode::BRM_LINE_LOOP);
    // Renderer::basicRenderPoint(m_node.x, m_node.y);
    // Renderer::basicRenderPoint(m_node.x, m_node.y - m_node.h);
    // Renderer::basicRenderPoint(m_node.x + m_node.w, m_node.y - m_node.h);
    // Renderer::basicRenderPoint(m_node.x + m_node.w, m_node.y);
    // Renderer::basicRenderEnd();

    Renderer::basicRenderPoint(m_node.x,m_node.y);
    Renderer::basicRenderPoint(m_node.x,m_node.y - m_node.h);

    Renderer::basicRenderPoint(m_node.x,m_node.y - m_node.h);
    Renderer::basicRenderPoint(m_node.x + m_node.w,m_node.y - m_node.h);

    Renderer::basicRenderPoint(m_node.x + m_node.w,m_node.y - m_node.h);
    Renderer::basicRenderPoint(m_node.x + m_node.w,m_node.y);

    Renderer::basicRenderPoint(m_node.x + m_node.w,m_node.y);
    Renderer::basicRenderPoint(m_node.x,m_node.y);


    
    if (m_hasBranched) {
        m_quadrant1->drawTree();
        m_quadrant2->drawTree();
        m_quadrant3->drawTree();
        m_quadrant4->drawTree();
    }

    
}

QuadTreeDemo::QuadTreeDemo() {

}

QuadTreeDemo::QuadTreeDemo(QuadTree quadTree) :
    m_quadTree(quadTree) {
    float randMinX = m_quadTree.m_node.x;
    float randMaxX = m_quadTree.m_node.x + m_quadTree.m_node.w;
    float randMaxY = m_quadTree.m_node.y;
    float randMinY = m_quadTree.m_node.y - m_quadTree.m_node.h;
    for (int i = 0; i < m_maxPoints; i++) {
        float randX = randMinX + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (randMaxX - randMinX);
        float randY = randMinY + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (randMaxY - randMinY);

        Point p = Point(
            randX,
            randY
        );
        m_quadTree.insertPoint(p);
    }
}

void QuadTreeDemo::show(){
    Renderer::basicRenderBegin(BasicRenderMode::BRM_LINES);
    m_quadTree.drawTree();
    Renderer::basicRenderEnd();

    Renderer::basicRenderBegin(BasicRenderMode::BRM_DOT);
    m_quadTree.drawPoints();
    Renderer::basicRenderEnd();
}

