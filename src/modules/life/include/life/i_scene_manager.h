#ifndef I_SCENE_MANAGER_H
#define I_SCENE_MANAGER_H

#include <QObject>
#include <vw/entity.h>
#include <vw/component.h>

class IScene: public vw::Entity
{
    Q_OBJECT
public:
    IScene(QObject *parent = nullptr):
        vw::Entity(parent)
    {}

    template<typename T>
    T *addEntity()
    {
        T * t = new T(this);
        addEntity(t);
    }

    virtual void addEntity(vw::Entity *entity) = 0;
    virtual void removeEntity(vw::Entity *entity) = 0;

    virtual void selectEntity(vw::Entity *entity) = 0;
    virtual void deselectEntity(vw::Entity *entity) = 0;
    virtual QList<vw::Entity *> selectedEntities() = 0;

    virtual void setCurrentEntity(vw::Entity *entity) = 0;
    virtual vw::Entity *currentEntity() = 0;
};

class ISceneManager
{
public:
    virtual ~ISceneManager(){}

    virtual IScene *createScene(const QString &name) = 0;
    virtual void removeScene(IScene *scene) = 0;

    virtual IScene *getSceneByName(const QString &name) = 0;
    virtual QList<IScene *> getSceneList() = 0;

    virtual IScene *currentScene() = 0;
    virtual void setCurrentScene(IScene *scene) = 0;
};

#define ISceneManager_iid "snow.dream.iscenemanager"
Q_DECLARE_INTERFACE(ISceneManager, ISceneManager_iid)

#endif // I_SCENE_MANAGER_H
