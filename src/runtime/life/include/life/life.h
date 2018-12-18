#ifndef LIFE_H
#define LIFE_H

#include "life_global.h"
#include <QObject>
#include <QList>
#include <memory>
#include "scene.h"

namespace dream
{

class LIFE_DECL Life: public QObject
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
    void sceneAdded(Scene *);
    void sceneRemoved(Scene *);
    void currentSceneChanged(Scene *);

private:
	class Imp;
	std::unique_ptr<Imp> imp_;
};

} // namespace dream

#endif // LIFE_H
