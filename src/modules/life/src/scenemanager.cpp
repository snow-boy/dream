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

IScene *SceneManager::createScene(const QString &name)
{
     Scene *scene = new Scene(this);
    scene->setObjectName(name);
    scene_list_.append(scene);

    EntityEvent event(Evt_SceneAdded, scene);
    Cradle::postEvent(&event, this);

    if(current_scene_ == nullptr){
        setCurrentScene(scene);
    }

    return scene;
}

void SceneManager::removeScene(IScene *scene)
{
    Q_ASSERT(scene_list_.contains(scene));
    if(current_scene_ == scene){
        setCurrentScene(nullptr);
    }

    scene_list_.removeOne(scene);
    scene->setParent(nullptr);

    if(scene_list_.size() > 0){
        setCurrentScene(scene_list_.first());
    }

    EntityEvent event(Evt_SceneRemoved, QSharedPointer<IScene>(scene));
    Cradle::postEvent(&event, this);
}

IScene *SceneManager::getSceneByName(const QString &name)
{
    IScene *scene = nullptr;

    for(IScene *e: scene_list_){
        if(e->objectName() == name){
            scene = e;
            break;
        }
    }

    return scene;
}

QList<IScene *> SceneManager::getSceneList()
{
    return scene_list_;
}

IScene *SceneManager::currentScene()
{
    return current_scene_;
}

void SceneManager::setCurrentScene(IScene *scene)
{
    Q_ASSERT(scene == nullptr || scene_list_.contains(scene));
    if(scene != current_scene_){
        current_scene_ = scene;

        EntityEvent event(Evt_CurrentSceneChanged, scene);
        Cradle::postEvent(&event, this);
    }
}
