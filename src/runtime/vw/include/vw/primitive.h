#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QColor>
#include "entity.h"
#include "component.h"

namespace vw {

class VW_DECL TexCoord : public Component
{
    Q_OBJECT
public:
    TexCoord(QObject *parent = nullptr):
        Component(parent)
    {}

    void setData(const QVector2D &data) { data_ = data; }
    QVector2D data() const { return data_; }

private:
    QVector2D data_;
};

class VW_DECL Color : public Component
{
    Q_OBJECT
public:
    Color(QObject *parent = nullptr):
        Component(parent)
    {}

    void setData(const QColor &color) { color_ = color; }
    QColor data() const { return color_; }

private:
    QColor color_;
};

class VW_DECL Vertex : public Entity
{
    Q_OBJECT
public:
    Vertex(QObject *parent = nullptr):
        Entity (parent)
    {}

    void setData(const QVector3D &data) { data_ = data; }
    QVector3D data() const { return data_; }

private:
    QVector3D data_;
};


class VW_DECL Primitive : public Entity
{
    Q_OBJECT
public:
    enum PrimitiveType
    {
        POINTS,
        LINES,
        LINE_LOOP,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        QUADS,
        QUAD_STRIP,
        POLYGON
    };

    Primitive(PrimitiveType type, QObject *parent = nullptr):
        Entity (parent),
        type_ (type)
    {}

    PrimitiveType primitiveType() const { return type_; }

    void addVertex(Vertex *vertex)
    {
        vertex_list_.append(vertex);
    }

    void removeVertex(Vertex *vertex)
    {
        vertex_list_.removeAll(vertex);
    }

    QVector<Vertex *> vertexList() const
    {
        return vertex_list_;
    }

private:
    PrimitiveType type_;
    QVector<Vertex *> vertex_list_;
};

} // namespace vw

#endif // PRIMITIVE_H
