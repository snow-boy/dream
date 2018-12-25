#include "scene.h"
#include <QList>

namespace dream
{

class Scene::Imp
{
public:
    Imp():
        current_entity_(nullptr)
    {}

    QList<Entity *> entity_list_;
    Entity *current_entity_;
};

Scene::Scene(QObject *parent) :
    Entity (parent)
{
    imp_ = std::make_unique<Imp>();
}

Scene::~Scene()
{

}

void Scene::addEntity(Entity *entity)
{
    Q_ASSERT(!imp_->entity_list_.contains(entity));
    imp_->entity_list_.append(entity);
    entity->setParent(this);
    emit entityAdded(entity);

    if(imp_->current_entity_ == nullptr){
        setCurrentEntity(entity);
    }
}

void Scene::removeEntity(Entity *entity)
{
    Q_ASSERT(imp_->entity_list_.contains(entity));
    imp_->entity_list_.removeOne(entity);
    entity->setParent(nullptr);
    emit entityRemoved(entity);
}

void Scene::setCurrentEntity(Entity *entity)
{
    if(imp_->current_entity_ != entity){
        imp_->current_entity_ = entity;
        emit currentEntityChanged(entity);
    }
}

Entity *Scene::currentEntity()
{
    return imp_->current_entity_;
}

} // namespace dream

