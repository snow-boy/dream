#include "scene.h"
#include <cradle/cradle.h>
#include <events/events.h>

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

    EntityEvent event(Evt_EntityAdded, entity);
    Cradle::postEvent(&event, this);

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

    EntityEvent event(Evt_EntityRemoved, QSharedPointer<Entity>(entity));
    Cradle::postEvent(&event, this);
}

void Scene::selectEntity(vw::Entity *entity)
{
    Q_ASSERT(!selected_entities_.contains(entity));
    selected_entities_.append(entity);

    EntityEvent event(Evt_EntitySelected, entity);
    Cradle::postEvent(&event, this);
}

void Scene::deselectEntity(vw::Entity *entity)
{
    Q_ASSERT(selected_entities_.contains(entity));
    selected_entities_.removeAll(entity);

    EntityEvent event(Evt_EntityDeselected, entity);
    Cradle::postEvent(&event, this);
}

QList<vw::Entity *> Scene::selectedEntities()
{
    return selected_entities_;
}

void Scene::setCurrentEntity(Entity *entity)
{
    current_entity_ = entity;

    EntityEvent event(Evt_CurrentEntityChanged, entity);
    Cradle::postEvent(&event, this);
}

vw::Entity *Scene::currentEntity()
{
    return current_entity_;
}
