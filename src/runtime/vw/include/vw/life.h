#ifndef LIFE_H
#define LIFE_H

#include "vw_global.h"
#include <QObject>
#include <QList>
#include <memory>
#include "scene.h"

namespace dream
{

class VW_DECL Life: public QObject
{
    Q_OBJECT
public:
    Life();
	~Life();

    Scene *addScene(const QString &name);
    void removeScene(Scene *scene);
    QList<Scene *> sceneList();

    void setCurrentScene(Scene *scene);
    Scene *currentScene();

signals:
    void sceneAdded(dream::Scene *);
    void sceneRemoved(dream::Scene *);
    void currentSceneChanged(dream::Scene *);

private:
	class Imp;
	std::unique_ptr<Imp> imp_;
};

} // namespace dream

#endif // LIFE_H
