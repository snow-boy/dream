#include "modelcabinet.h"

#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>
#include <vw/life.h>
#include <cradle/cradle.h>

ModelCabinet::ModelCabinet(QWidget *parent) :
    Cabinet(parent)
{
    init();

    Cradle::registerSloter(this, SIGNAL(currentSceneChanged(Scene *)), SLOT(onCurrentSceneChanged(dream::Scene *scene)));
}

ModelCabinet::~ModelCabinet()
{
    Cradle::unregisterSloter(this);
}

void ModelCabinet::init()
{
    if(Cradle::findObject<dream::Life *>() != nullptr){
        setEnabled(true);
    }
    else{
        setDisabled(true);
    }
}

void ModelCabinet::onCurrentSceneChanged(dream::Scene *scene)
{
    if(scene != nullptr){
        setEnabled(true);
    }
    else{
        setDisabled(true);
    }
}
