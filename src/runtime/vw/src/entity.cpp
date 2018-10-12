#include "entity.h"

namespace vw {

class Entity::Imp
{
public:
    Imp():
        scale({1, 1, 1}),
        parent(nullptr)
    {}

    ~Imp()
    {}

    QList<Entity *> children;
    QList<std::shared_ptr<Component>> component_list;
    Entity *parent;

    QVector3D position;
    QQuaternion rotation;
    QVector3D scale;
};

Entity::Entity()
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

Entity *Entity::parent() const
{
    return imp_->parent;
}

void Entity::addChild(Entity *entity)
{
    imp_->children.append(entity);
    entity->imp_->parent = this;
    emit childAdded(entity);
}

void Entity::removeChild(Entity *entity)
{
    imp_->children.removeOne(entity);
    entity->imp_->parent = nullptr;
    emit childRemoved(entity);
}

QList<Entity *> Entity::entities() const
{
    return imp_->children;
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
    imp_->component_list.append(component);
    emit componentAdded(component);
}

void Entity::removeComponent(std::shared_ptr<Component> component)
{
    imp_->component_list.removeOne(component);
    emit componentRemoved(component);
}

QList<std::shared_ptr<Component> > Entity::components() const
{
    return imp_->component_list;
}

} // namespace vw
