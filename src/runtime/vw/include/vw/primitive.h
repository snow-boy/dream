#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QVector3D>
#include <QVector>

namespace vw {

enum PrimitiveType
{
    POINTS,
    LINES,
    STRIP,
    LINE_LOOP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    QUADS,
    QUAD_STRIP,
    POLYGON
};

struct Primitive
{
    PrimitiveType type;
    QVector<QVector3D> vertex;
};

} // namespace vw

#endif // PRIMITIVE_H
