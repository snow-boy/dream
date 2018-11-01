#include "geometry.h"

namespace vw {

class Geometry::Imp
{
public:
    ~Imp()
    {
        for(Primitive *e : primitives){
            delete e;
        }
        primitives.clear();
    }

    QVector<Primitive *> primitives;
};

Geometry::Geometry(QObject *parent):
    Entity(parent)
{
    imp_ = std::make_unique<Imp>();
}

Geometry::~Geometry()
{

}

void Geometry::addPrimitive(Primitive *prim)
{
    Q_ASSERT(!imp_->primitives.contains(prim));
    imp_->primitives.append(prim);
    emit primitiveAdded(prim);
}

void Geometry::removePrimitive(Primitive *prim)
{
    Q_ASSERT(imp_->primitives.contains(prim));
    imp_->primitives.removeOne(prim);
    emit primitiveRemoved(prim);
}

QVector<Primitive *> Geometry::primitives()
{
    return imp_->primitives;
}

}
