#include "cube.h"

namespace vw
{

class Cube::Imp
{
public:
    Imp():
        height(0.5f),
        is_build(false),
        top(nullptr),
        bottom(nullptr),
        front(nullptr),
        back(nullptr),
        left(nullptr),
        right(nullptr)
    {}

    float height;
    bool is_build;

    Primitive *top;
    Primitive *bottom;
    Primitive *front;
    Primitive *back;
    Primitive *left;
    Primitive *right;
};

Cube::Cube(QObject *parent):
    Geometry (parent)
{
    imp_ = std::make_unique<Imp>();
}

Cube::Cube(float height, QObject *parent):
    Cube(parent)
{
    setHeight(height);
    build();
}

Cube::~Cube()
{

}

void Cube::setHeight(float h)
{
    imp_->height = h;
}

float Cube::height() const
{
    return imp_->height;
}

void Cube::build()
{
    if(imp_->is_build){
        Q_ASSERT(false); // already built
        return;
    }

    float h = imp_->height;

    QVector3D top_vertexs_data[] =
    {
        {h/2.0f, h, h/2.0f},
        {-h/2.0f, h, h/2.0f},
        {-h/2.0f, h, -h/2.0f},
        {h/2.0f, h, -h/2.0f}
    };

    Vertex* top_vertexs[4];
    for(int i = 0; i < 4; ++i){
        top_vertexs[i] = new Vertex(this);
        top_vertexs[i]->setData(top_vertexs_data[i]);
    }

    QVector3D bottom_vertexs_data[] =
    {
        {h/2.0f, 0, h/2.0f},
        {-h/2.0f, 0, h/2.0f},
        {-h/2.0f, 0, -h/2.0f},
        {h/2.0f, 0, -h/2.0f}
    };

    Vertex* bottom_vertexs[4];
    for(int i = 0; i < 4; ++i){
        bottom_vertexs[i] = new Vertex(this);
        bottom_vertexs[i]->setData(bottom_vertexs_data[i]);
    }

    Primitive *bottom = new Primitive(Primitive::QUADS, this);
    {
        for(int i = 0; i < 4; ++i){
            bottom->addVertex(bottom_vertexs[i]);
        }
    }
    imp_->bottom = bottom;
    addPrimitive(bottom);

    Primitive *top = new Primitive(Primitive::QUADS, this);
    {
        for(int i = 0; i < 4; ++i){
            top->addVertex(top_vertexs[i]);
        }
    }
    imp_->top = top;
    addPrimitive(top);

    Primitive *left = new Primitive(Primitive::QUADS, this);
    {
        left->addVertex(top_vertexs[1]);
        left->addVertex(top_vertexs[2]);
        left->addVertex(bottom_vertexs[2]);
        left->addVertex(bottom_vertexs[1]);
    }
    imp_->left = left;
    addPrimitive(left);

    Primitive *right = new Primitive(Primitive::QUADS, this);
    {
        right->addVertex(top_vertexs[0]);
        right->addVertex(top_vertexs[3]);
        right->addVertex(bottom_vertexs[3]);
        right->addVertex(bottom_vertexs[0]);
    }
    imp_->right = right;
    addPrimitive(right);

    Primitive *front = new Primitive(Primitive::QUADS, this);
    {
        front->addVertex(top_vertexs[0]);
        front->addVertex(top_vertexs[1]);
        front->addVertex(bottom_vertexs[1]);
        front->addVertex(bottom_vertexs[0]);
    }
    imp_->front = front;
    addPrimitive(front);

    Primitive *back = new Primitive(Primitive::QUADS, this);
    {
        back->addVertex(top_vertexs[2]);
        back->addVertex(top_vertexs[3]);
        back->addVertex(bottom_vertexs[3]);
        back->addVertex(bottom_vertexs[2]);
    }
    imp_->back = back;
    addPrimitive(back);
}

Primitive *Cube::bottom() const
{
    Q_ASSERT(imp_->bottom != nullptr);
    return imp_->bottom;
}

Primitive *Cube::top() const
{
    Q_ASSERT(imp_->top != nullptr);
    return imp_->top;
}

Primitive *Cube::front() const
{
    Q_ASSERT(imp_->front != nullptr);
    return imp_->front;
}

Primitive *Cube::back() const
{
    Q_ASSERT(imp_->back != nullptr);
    return imp_->back;
}

Primitive *Cube::left() const
{
    Q_ASSERT(imp_->left != nullptr);
    return imp_->left;
}

Primitive *Cube::right() const
{
    Q_ASSERT(imp_->right != nullptr);
    return imp_->right;
}

} // namespace vw
