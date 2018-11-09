#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vw_global.h"
#include "entity.h"
#include "primitive.h"

namespace vw{

class VW_DECL Geometry : public Entity
{
    Q_OBJECT
public:
    Geometry(QObject *parent = nullptr);
    ~Geometry();

    void addPrimitive(Primitive *prim);
    void removePrimitive(Primitive *prim);
    void clearPrimitives();

    QVector<Primitive *> primitives();

signals:
    void primitiveAdded(Primitive *prim);
    void primitiveRemoved(Primitive *prim);

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

}

#endif // GEOMETRY_H
