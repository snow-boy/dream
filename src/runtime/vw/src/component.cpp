#include "component.h"

namespace dream {

class Component::Imp
{
public:
    QList<Entity *> entity_list;
};

Component::Component(QObject *parent):
    QObject (parent)
{
    imp_ = std::make_unique<Imp>();
}

Component::~Component()
{

}

void Component::addToEntity(Entity *entity)
{
    Q_ASSERT(!imp_->entity_list.contains(entity));
    imp_->entity_list.append(entity);
    emit addedToEntity(entity);
}

void Component::removeFromEntity(Entity *entity)
{
    Q_ASSERT(imp_->entity_list.contains(entity));
    imp_->entity_list.removeOne(entity);
    emit removedFromEntity(entity);
}

QList<Entity *> Component::entities()
{
    return imp_->entity_list;
}

} // namespace dream
