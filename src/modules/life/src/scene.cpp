#include "scene.h"
#include <cradle/cradle.h>

Scene::Scene(QObject *parent):
    IScene (parent),
    current_entity_(nullptr)
{

}

Scene::~Scene()
{

}

void Scene::addEntity(vw::Entity *entity)
{
    if(entity->parent() != this){
        entity->setParent(this);
    }
    emit sigEntityAdded(this, entity);

    if(current_entity_ == nullptr){
        setCurrentEntity(current_entity_);
    }
}

void Scene::removeEntity(vw::Entity *entity)
{
    selected_entities_.removeAll(entity);
    if(current_entity_ == entity){
        setCurrentEntity(nullptr);
    }
    entity->setParent(nullptr);

    emit sigEntityRemoved(this, entity);
    entity->deleteLater();
}

void Scene::selectEntity(vw::Entity *entity)
{
    Q_ASSERT(!selected_entities_.contains(entity));
    selected_entities_.append(entity);
    emit sigEntitySelected(this, entity);
}

void Scene::deselectEntity(vw::Entity *entity)
{
    Q_ASSERT(selected_entities_.contains(entity));
    selected_entities_.removeAll(entity);
    emit sigEntityDeselected(this, entity);
}

QList<vw::Entity *> Scene::selectedEntities()
{
    return selected_entities_;
}

void Scene::setCurrentEntity(Entity *entity)
{
    if(entity != current_entity_){
        current_entity_ = entity;
        emit sigCurrentEntityChanged(this, entity);
    }
}

vw::Entity *Scene::currentEntity()
{
    return current_entity_;
}
