#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "i_scene_manager.h"
#include "scene.h"

class SceneManager:
        public QObject,
        public ISceneManager
{
    Q_OBJECT
public:
    SceneManager(QObject *parent = nullptr);
    ~SceneManager();

    // ISceneManager interface
    virtual IScene *createScene(const QString &name) override;
    virtual void removeScene(IScene *scene) override;
    virtual IScene *getSceneByName(const QString &name) override;
    virtual QList<IScene *> getSceneList() override;
    virtual IScene *currentScene() override;
    virtual void setCurrentScene(IScene *scene) override;

private:
    QList<IScene *> scene_list_;
    IScene *current_scene_;
};

#endif // SCENEMANAGER_H
