#include "cone.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace vw
{

class Cone::Imp
{
public:
    Imp():
        bottom_r(0.25f),
        height(0.5f),
        segments(10)
    {}

    float bottom_r;
    float height;
    int segments;
};

Cone::Cone(QObject *parent):
    Geometry (parent)
{
    imp_ = std::make_unique<Imp>();
    build();
}

Cone::~Cone()
{

}

void Cone::setBottomR(float r)
{
    imp_->bottom_r = r;
    clearPrimitives();
    build();
}

float Cone::bottomR() const
{
    return imp_->bottom_r;
}

void Cone::setHeight(float height)
{
    imp_->height = height;
    clearPrimitives();
    build();
}

float Cone::height() const
{
    return imp_->height;
}

void Cone::setSegments(int segments)
{
    imp_->segments = segments;
    clearPrimitives();
    build();
}

int Cone::segments() const
{
    return imp_->segments;
}

void Cone::build()
{
    Vertex *top_vertex = new Vertex(this);
    top_vertex->setData(QVector3D(0, imp_->height, 0));

    QVector<Vertex *> bottom_vertexs;
    float radius_step = 360.0f / imp_->segments;
    for(int i = 0; i < imp_->segments; ++i){
        Vertex *vertex = new Vertex(this);
        vertex->setData(QVector3D(imp_->bottom_r * cos(radius_step*i/180.0f*M_PI),
                                  0,
                                  imp_->bottom_r * sin(radius_step*i/180.0f*M_PI)));
        bottom_vertexs.append(vertex);
    }

    Primitive *bottom = new Primitive(Primitive::POLYGON, this);
    for(int i = 0; i < imp_->segments + 1; ++i){
        bottom->addVertex(bottom_vertexs[i%imp_->segments]);
    }
    addPrimitive(bottom);

    Primitive *side = new Primitive(Primitive::TRIANGLE_FAN, this);
    side->addVertex(top_vertex);
    for(int i = 0; i < imp_->segments + 1; ++i){
        side->addVertex(bottom_vertexs[i%imp_->segments]);
    }
    addPrimitive(side);
}

}
