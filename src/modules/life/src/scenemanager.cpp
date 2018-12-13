#include "scenemanager.h"
#include <cradle/cradle.h>
#include <events/events.h>

SceneManager::SceneManager(QObject *parent):
    QObject (parent),
    current_scene_(nullptr)
{
}

SceneManager::~SceneManager()
{
}

vw::Entity *SceneManager::createScene(const QString &name)
{
    vw::Entity *scene = new vw::Entity(this);
    scene->setObjectName(name);
    scene_list_.append(scene);

    return scene;
}

void SceneManager::removeScene(vw::Entity *scene)
{
    Q_ASSERT(scene_list_.contains(scene));
    scene_list_.removeOne(scene);
}

vw::Entity *SceneManager::getSceneByName(const QString &name)
{
    vw::Entity *scene = nullptr;

    for(vw::Entity *e: scene_list_){
        if(e->objectName() == name){
            scene = e;
            break;
        }
    }

    return scene;
}

QList<vw::Entity *> SceneManager::getSceneList()
{
    return scene_list_;
}

vw::Entity *SceneManager::currentScene()
{
    return current_scene_;
}

void SceneManager::setCurrentScene(vw::Entity *scene)
{
    Q_ASSERT(scene == nullptr || scene_list_.contains(scene));
    if(scene != current_scene_){
        current_scene_ = scene;
    }
}
