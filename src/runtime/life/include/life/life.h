#ifndef LIFE_H
#define LIFE_H

#include <memory>

#include <QObject>
#include <QString>
#include <QList>

#include <vw/entity.h>
#include "life_global.h"

class LIFE_DECL Life : public QObject
{
    Q_OBJECT
public:
    static Life *get();

    vw::Entity *createScene(const QString &name);
    void destoryScene(const QString &name);

    vw::Entity *getSceneByName(const QString &name);
    QList<vw::Entity *> getSceneList();

    vw::Entity *currentScene();
    void setCurrentScene(const QString &name);
    void setCurrentScene(vw::Entity *scene);

    void updateScene(const QString &scene_name);
    void updateScene(vw::Entity *scene);

    void updateCurrentScene();

signals:
    void onSceneCreated(vw::Entity *scene);
    void onWillDestoryScene(vw::Entity *scene);
    void onCurrentSceneChanged(vw::Entity *scene);
    void onSceneUpdated(vw::Entity *scene);
    void onCurrentSceneUpdated();

public slots:

private:
    Life();
    ~Life();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

#endif // LIFE_H
