#ifndef CUBE_H
#define CUBE_H

#include "geometry.h"

namespace vw
{

class VW_DECL Cube : public Geometry
{
    Q_OBJECT
public:
    explicit Cube(QObject *parent = nullptr);
    ~Cube();

    void setLength(float l);
    float length() const;

    void setWidth(float w);
    float width() const;

    void setHeight(float h);
    float height() const;

    Primitive *bottom() const;
    Primitive *top() const;
    Primitive *front() const;
    Primitive *back() const;
    Primitive *left() const;
    Primitive *right() const;

private:
    void build();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // CUBE_H
