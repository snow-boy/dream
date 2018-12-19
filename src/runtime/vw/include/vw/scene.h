#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <memory>
#include "entity.h"

namespace dream
{

class VW_DECL Scene : public Entity
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);

    void setCurrentEntity(Entity *entity);
    Entity *currentEntity();

signals:
    void entityAdded(Entity *);
    void entityRemoved(Entity *);
    void currentEntityChanged(Entity *);

public slots:

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace dream

#endif // SCENE_H
