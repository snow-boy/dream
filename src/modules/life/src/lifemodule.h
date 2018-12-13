#ifndef LIFEMODULE_H
#define LIFEMODULE_H

#include <QObject>
#include "scenemanager.h"

#define LIFE_IID "dream.modules.life"

class LifeModule :
        public QObject,
        public ISceneManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LIFE_IID)
    Q_INTERFACES(ISceneManager)

public:
    explicit LifeModule(QObject *parent = nullptr);
    ~LifeModule();

    // ISceneManager interface
    virtual vw::Entity *createScene(const QString &name) override
    { return scene_manager_->createScene(name); }
    virtual void removeScene(vw::Entity *scene) override
    { scene_manager_->removeScene(scene); }
    virtual vw::Entity *getSceneByName(const QString &name) override
    { return scene_manager_->getSceneByName(name); }
    virtual QList<vw::Entity *> getSceneList() override
    { return scene_manager_->getSceneList(); }
    virtual vw::Entity *currentScene() override
    { return scene_manager_->currentScene(); }
    virtual void setCurrentScene(vw::Entity *scene) override
    { scene_manager_->setCurrentScene(scene); }

signals:

public slots:

private:
    SceneManager *scene_manager_;
};

#endif // LIFEMODULE_H
