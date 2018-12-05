#include "entity.h"
#include "component.h"

namespace vw {

class Entity::Imp
{
public:
    Imp():
        scale({1, 1, 1})
    {}

    ~Imp()
    {}

    QList<Component *> component_list;

    QVector3D offset;
    QVector3D position;
    QQuaternion rotation;
    QVector3D scale;
    QMatrix4x4 pivot;
};

Entity::Entity(QObject *parent):
    QObject(parent)
{
    imp_ = std::make_unique<Imp>();
}

Entity::~Entity()
{

}

void Entity::setPosition(const QVector3D &pos)
{
    imp_->position = pos;
    emit positionChanged(pos);
}

QVector3D Entity::position() const
{
    return imp_->position;
}

void Entity::setOffset(const QVector3D &offset)
{
    imp_->offset = offset;
}

QVector3D Entity::offset() const
{
    return imp_->offset;
}

void Entity::setRotation(const QQuaternion &q)
{
    imp_->rotation = q;
    emit rotaionChanged(q);
}

QQuaternion Entity::rotation() const
{
    return imp_->rotation;
}

void Entity::setScale(const QVector3D &scale)
{
    imp_->scale = scale;
    emit scaleChanged(scale);
}

QVector3D Entity::scale() const
{
    return imp_->scale;
}

void Entity::setPivot(const QMatrix4x4 &pivot)
{
    imp_->pivot = pivot;
}

QMatrix4x4 Entity::pivot() const
{
    return imp_->pivot;
}

void Entity::addComponent(Component *component)
{
    Q_ASSERT(!imp_->component_list.contains(component));
    imp_->component_list.append(component);
    component->addToEntity(this);
    emit componentAdded(component);
}

void Entity::removeComponent(Component *component)
{
    Q_ASSERT(imp_->component_list.contains(component));
    imp_->component_list.removeOne(component);
    component->removedFromEntity(this);
    emit componentRemoved(component);
}

QList<Component *> Entity::components() const
{
    return imp_->component_list;
}

} // namespace vw
