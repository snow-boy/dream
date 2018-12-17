#include "lifemodule.h"
#include <cradle/cradle.h>

LifeModule::LifeModule(QObject *parent) :
    QObject(parent)
{
    scene_manager_ = new SceneManager;
}

LifeModule::~LifeModule()
{
    if(scene_manager_ != nullptr){
        delete scene_manager_;
        scene_manager_ = nullptr;
    }
}
