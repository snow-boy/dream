#include "life.h"

class Life::Imp
{
public:
    QList<vw::Entity *> scene_list_;
    vw::Entity *current_scene_;
};

Life *Life::get()
{
    static Life the_life;
    return &the_life;
}

vw::Entity *Life::createScene(const QString &name)
{
    vw::Entity *scene = new vw::Entity;
    scene->setObjectName(name);
    imp_->scene_list_.append(scene);

    return scene;
}

void Life::destoryScene(const QString &name)
{
    vw::Entity *scene = getSceneByName(name);
    if(scene != nullptr){
        imp_->scene_list_.removeOne(scene);
        delete scene;
    }
}

vw::Entity *Life::getSceneByName(const QString &name)
{
    vw::Entity *scene = nullptr;
    for(vw::Entity *e: imp_->scene_list_){
        if(e->objectName() == name){
            scene = e;
            break;
        }
    }

    return scene;
}

QList<vw::Entity *> Life::getSceneList()
{
    return imp_->scene_list_;
}

vw::Entity *Life::currentScene()
{
    return imp_->current_scene_;
}

void Life::setCurrentScene(const QString &name)
{
    vw::Entity *scene = getSceneByName(name);
    if(scene != nullptr){
        setCurrentScene(scene);
    }
}

void Life::setCurrentScene(vw::Entity *scene)
{
    if(scene != imp_->current_scene_){
        imp_->current_scene_ = scene;
        emit onCurrentSceneChanged(scene);
    }
}

void Life::updateScene(const QString &scene_name)
{
    vw::Entity *scene = getSceneByName(scene_name);
    if(scene != nullptr){
        updateScene(scene);
    }
}

void Life::updateScene(vw::Entity *scene)
{
    emit onSceneUpdated(scene);
    if(scene == imp_->current_scene_){
        emit onCurrentSceneUpdated();
    }
}

void Life::updateCurrentScene()
{
    if(imp_->current_scene_ != nullptr){
        emit onSceneUpdated(imp_->current_scene_);
        emit onCurrentSceneUpdated();
    }
}

Life::Life()
{
    imp_ = std::make_unique<Imp>();
}

Life::~Life()
{

}
