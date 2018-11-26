#include "grid.h"

namespace vw
{

class Grid::Imp
{
public:
    Imp():
        width(1.0f),
        width_div_count(20),
        length(1.0f),
        length_div_count(20)
    {}

    float width;
    int width_div_count;

    float length;
    int length_div_count;
};

Grid::Grid(QObject *parent):
    Geometry (parent)
{
    imp_ = std::make_unique<Imp>();

    build();
}

Grid::~Grid()
{

}

void Grid::setWidth(float w, int div_count)
{
    imp_->width = w;
    imp_->width_div_count = div_count;

    clearPrimitives();
    build();
}

float Grid::width() const
{
    return imp_->width;
}

int Grid::widthDivCount() const
{
    return imp_->width_div_count;
}

void Grid::setLength(float l, int div_count)
{
    imp_->length = l;
    imp_->length_div_count = div_count;

    clearPrimitives();
    build();
}

float Grid::Length() const
{
    return imp_->length;
}

int Grid::lengthDivCount() const
{
    return imp_->length_div_count;
}

void Grid::build()
{
    Primitive *lines = new Primitive(Primitive::LINES, this);

    float length_step = imp_->length/imp_->length_div_count;
    for(int i = -imp_->length_div_count/2; i < imp_->length_div_count/2 + 1; ++i){
        Vertex *v1 = new Vertex(this);
        v1->setData({i * length_step, 0, imp_->width/2});
        lines->addVertex(v1);

        Vertex *v2 = new Vertex(this);
        v2->setData({i * length_step, 0, -imp_->width/2});
        lines->addVertex(v2);
    }

    float width_step = imp_->width/imp_->width_div_count;
    for(int i = -imp_->width_div_count/2; i < imp_->width_div_count/2 + 1; ++i){
        Vertex *v1 = new Vertex(this);
        v1->setData({imp_->length/2, 0, i * width_step});
        lines->addVertex(v1);

        Vertex *v2 = new Vertex(this);
        v2->setData({-imp_->length/2, 0, i * width_step});
        lines->addVertex(v2);
    }

    addPrimitive(lines);
}

} // namespace vw
