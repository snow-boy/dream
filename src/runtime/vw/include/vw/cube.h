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
    Cube(float height, QObject *parent = nullptr);
    ~Cube();

    void setHeight(float h);
    float height() const;

    void build();

    Primitive *bottom() const;
    Primitive *top() const;
    Primitive *front() const;
    Primitive *back() const;
    Primitive *left() const;
    Primitive *right() const;

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // CUBE_H
