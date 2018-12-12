#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "i_scene_manager.h"

class SceneManager:
        public QObject,
        public ISceneManager
{
    Q_OBJECT
public:
    SceneManager(QObject *parent = nullptr);
    ~SceneManager();

    // ISceneManager interface
    virtual vw::Entity *createScene(const QString &name) override;
    virtual void destoryScene(vw::Entity *scene) override;
    virtual vw::Entity *getSceneByName(const QString &name) override;
    virtual QList<vw::Entity *> getSceneList() override;
    virtual vw::Entity *currentScene() override;
    virtual void setCurrentScene(vw::Entity *scene) override;

    // QObject interface
    virtual bool event(QEvent *e) override;

private:
    QList<vw::Entity *> scene_list_;
    vw::Entity *current_scene_;
};

#endif // SCENEMANAGER_H
