#include "lifemodule.h"

LifeModule::LifeModule(QObject *parent) :
    QObject(parent)
{
    scene_manager_ = new SceneManager(this);
}

LifeModule::~LifeModule()
{

}
