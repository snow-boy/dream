#include "life.h"

namespace dream
{

class Life::Imp
{
public:
    Imp():
        current_scene(nullptr)
    {}

    QList<Scene *> scene_list;
    Scene *current_scene;
};

Life::Life()
{
    imp_ = std::make_unique<Imp>();
}

Life::~Life()
{

}

Scene *Life::addScene(const QString &name)
{
    Scene *scene = new Scene(this);
    scene->setObjectName(name);
    imp_->scene_list.append(scene);
    emit sceneAdded(scene);

    if(currentScene() == nullptr){
        setCurrentScene(scene);
    }

    return scene;
}

void Life::removeScene(Scene *scene)
{
    Q_ASSERT(imp_->scene_list.contains(scene));
    imp_->scene_list.removeOne(scene);
    emit sceneRemoved(scene);
    scene->deleteLater();
}

QList<Scene *> Life::sceneList()
{
    return imp_->scene_list;
}

void Life::setCurrentScene(Scene *scene)
{
    if(scene != imp_->current_scene){
        imp_->current_scene = scene;
        emit currentSceneChanged(scene);
    }
}

Scene *Life::currentScene()
{
    return imp_->current_scene;
}

} //namespace dream
