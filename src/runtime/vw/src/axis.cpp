#include "axis.h"
#include "cone.h"

namespace vw
{

class Axis::Imp
{
public:
    Imp():
        is_array_visible_(true),
        axis_len_(5),
        arrow_bottom_r_(0.15),
        arrow_len_(0.5),
        arrow_segments_(10)
    {}

    bool is_array_visible_;
    float axis_len_;

    float arrow_bottom_r_;
    float arrow_len_;
    int arrow_segments_;
};

Axis::Axis(QObject *parent) : Geometry(parent)
{
    imp_ = std::make_unique<Imp>();
    build();
}

Axis::~Axis()
{

}

void Axis::hideArray()
{
    imp_->is_array_visible_ = false;
    clearPrimitives();
    build();
}

void Axis::showArray()
{
    imp_->is_array_visible_ = true;
    clearPrimitives();
    build();
}

void Axis::setArrowBottomR(float r)
{
    imp_->arrow_bottom_r_ = r;
    clearPrimitives();
    build();
}

float Axis::arrowBottomR()
{
    return imp_->arrow_bottom_r_;
}

void Axis::setArrowLength(float length)
{
    imp_->arrow_len_ = length;
    clearPrimitives();
    build();
}

float Axis::arrowLength()
{
    return imp_->arrow_len_;
}

void Axis::setArrowSegments(int segments)
{
    imp_->arrow_segments_ = segments;
    clearPrimitives();
    build();
}

int Axis::arrowSegments()
{
    return imp_->arrow_segments_;
}

void Axis::setLength(float len)
{
    imp_->axis_len_ = len;
    clearPrimitives();
    build();
}

float Axis::length()
{
    return imp_->axis_len_;
}

void Axis::build()
{
    // X
    {
        Color *color = new Color(this);
        color->setData(Qt::red);

        Vertex *origin = new Vertex(this);
        origin->setData({0, 0, 0});

        Vertex *x_end = new Vertex(this);
        x_end->setData({imp_->axis_len_ - imp_->arrow_len_, 0, 0});

        Primitive *x_axis = new Primitive(Primitive::LINES, this);
        x_axis->addVertex(origin);
        x_axis->addVertex(x_end);
        x_axis->addComponent(color);
        addPrimitive(x_axis);

        Cone *arrow = new Cone(this);
        arrow->setBottomR(imp_->arrow_bottom_r_);
        arrow->setHeight(imp_->arrow_len_);
        arrow->setSegments(imp_->arrow_segments_);
        arrow->setRotation(QQuaternion::fromAxisAndAngle({0, 0, 1}, -90));
        arrow->setPosition({0, imp_->axis_len_ - imp_->arrow_len_ + imp_->arrow_len_/2.0f, 0});
        arrow->addComponent(color);
    }

    // Y
    {
        Color *color = new Color(this);
        color->setData(Qt::green);

        Vertex *origin = new Vertex(this);
        origin->setData({0, 0, 0});

        Vertex *y_end = new Vertex(this);
        y_end->setData({0, imp_->axis_len_ - imp_->arrow_len_, 0});

        Primitive *y_axis = new Primitive(Primitive::LINES, this);
        y_axis->addVertex(origin);
        y_axis->addVertex(y_end);
        y_axis->addComponent(color);
        addPrimitive(y_axis);

        Cone *arrow = new Cone(this);
        arrow->setBottomR(imp_->arrow_bottom_r_);
        arrow->setHeight(imp_->arrow_len_);
        arrow->setSegments(imp_->arrow_segments_);
        arrow->setPosition({0, imp_->axis_len_ - imp_->arrow_len_ + imp_->arrow_len_/2.0f, 0});
        arrow->addComponent(color);
    }

    // Z
    {
        Color *color = new Color(this);
        color->setData(Qt::blue);

        Vertex *origin = new Vertex(this);
        origin->setData({0, 0, 0});

        Vertex *z_end = new Vertex(this);
        z_end->setData({0, 0, imp_->axis_len_ - imp_->arrow_len_});

        Primitive *z_axis = new Primitive(Primitive::LINES, this);
        z_axis->addVertex(origin);
        z_axis->addVertex(z_end);
        z_axis->addComponent(color);
        addPrimitive(z_axis);

        Cone *arrow = new Cone(this);
        arrow->setBottomR(imp_->arrow_bottom_r_);
        arrow->setHeight(imp_->arrow_len_);
        arrow->setSegments(imp_->arrow_segments_);
        arrow->setRotation(QQuaternion::fromAxisAndAngle({1, 0, 0}, 90));
        arrow->setPosition({0, imp_->axis_len_ - imp_->arrow_len_ + imp_->arrow_len_/2.0f, 0});
        arrow->addComponent(color);
    }
}

} // namespace vw
