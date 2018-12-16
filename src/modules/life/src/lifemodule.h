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
    virtual ~LifeModule() override;

    // ISceneManager interface
    virtual IScene *createScene(const QString &name) override
    { return scene_manager_->createScene(name); }
    virtual void removeScene(IScene *scene) override
    { scene_manager_->removeScene(scene); }
    virtual IScene *getSceneByName(const QString &name) override
    { return scene_manager_->getSceneByName(name); }
    virtual QList<IScene *> getSceneList() override
    { return scene_manager_->getSceneList(); }
    virtual IScene *currentScene() override
    { return scene_manager_->currentScene(); }
    virtual void setCurrentScene(IScene *scene) override
    { scene_manager_->setCurrentScene(scene); }

signals:

public slots:

private:
    SceneManager *scene_manager_;
};

#endif // LIFEMODULE_H
