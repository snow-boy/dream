#include "propcabinet.h"
#include <cradle/cradle.h>
#include <vw/life.h>
#include <vw/scene.h>

PropCabinet::PropCabinet(QWidget *parent):
    Cabinet (parent)
{
    init();

    Cradle::registerSloter(this, SIGNAL(), SLOT(onCurrentEntityChanged(dream::Entity *entity)));
}

PropCabinet::~PropCabinet()
{
    Cradle::unregisterSloter(this);
}

void PropCabinet::init()
{
    geo_editor_ = new GeometryEditor;
    addDrawer(geo_editor_);

    dream::Scene *current_scene = Cradle::findObject<dream::Life *>()->currentScene();
    if(current_scene != nullptr && (current_entity_ = current_scene->currentEntity()) != nullptr)
    {
        setEnabled(true);
        setCurrentEntity(current_entity_);
    }
    else
    {
        setDisabled(true);
    }
}

void PropCabinet::setCurrentEntity(dream::Entity *entity)
{
    current_entity_ = entity;
    dream::Geometry *geo = qobject_cast<dream::Geometry *>(entity);
    if(geo != nullptr){
        geo_editor_->setGemetry(geo);
    }
}

void PropCabinet::onCurrentEntityChanged(dream::Entity *entity)
{
    dream::Scene *sender_scene = qobject_cast<dream::Scene *>(sender());
    dream::Scene *current_scene = Cradle::findObject<dream::Life *>()->currentScene();
    if(sender_scene == current_scene){
        setCurrentEntity(entity);
    }
}

void PropCabinet::onCurrentSceneChanged(dream::Scene *scene)
{
    if(scene != nullptr){
        setCurrentEntity(scene->currentEntity());
    }
    else{
        setCurrentEntity(nullptr);
    }
}
