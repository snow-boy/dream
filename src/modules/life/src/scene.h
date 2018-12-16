#ifndef SCENE_H
#define SCENE_H

#include "i_scene_manager.h"

class Scene: public IScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);
    virtual ~Scene() override;

    virtual void addEntity(vw::Entity *entity) override;
    virtual void removeEntity(vw::Entity *entity) override;

    virtual void selectEntity(vw::Entity *entity) override;
    virtual void deselectEntity(vw::Entity *entity) override;
    virtual QList<vw::Entity *> selectedEntities() override;

    virtual void setCurrentEntity(vw::Entity *entity) override;
    virtual vw::Entity *currentEntity() override;

private:
    QList<vw::Entity *> selected_entities_;
    vw::Entity *current_entity_;
};

#endif // SCENE_H
