#ifndef SCENE_H
#define SCENE_H

#include "entity.h"

namespace vw {

class VW_DECL Scene: public Entity
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);
    ~Scene();

    template<typename T>
    T *addEntity()
    {
        return new T(this);
    }

    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);

    void selectEntity(Entity *entity);
    void deselectEntity(Entity *entity);

    void setCurrentEntity(Entity *entity);
    Entity *currentEntity();

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

}

#endif // SCENE_H
