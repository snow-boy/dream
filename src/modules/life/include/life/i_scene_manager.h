#ifndef I_SCENE_MANAGER_H
#define I_SCENE_MANAGER_H

#include <QObject>
#include <vw/entity.h>

class ISceneManager
{
public:
    virtual vw::Entity *createScene(const QString &name) = 0;
    virtual void destoryScene(vw::Entity *scene) = 0;

    virtual vw::Entity *getSceneByName(const QString &name) = 0;
    virtual QList<vw::Entity *> getSceneList() = 0;

    virtual vw::Entity *currentScene() = 0;
    virtual void setCurrentScene(vw::Entity *scene) = 0;
};

#define ISceneManager_iid "snow.dream.iscenemanager"
Q_DECLARE_INTERFACE(ISceneManager, ISceneManager_iid)

#endif // I_SCENE_MANAGER_H
