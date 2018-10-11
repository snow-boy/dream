#ifndef ENTITY_H
#define ENTITY_H

#include "vw_global.h"
#include <QObject>
#include <QList>
#include "component.h"

namespace vw {

class VW_DECL Entity : public QObject
{
    Q_OBJECT
public:
    Entity();

    void addChild(Entity *entity);
    void removeChild(Entity *entity);
    QList<Entity *> entities();

    void addComponent(Component *component);
    void removeComponent(Component *component);
    QList<Component *> components();
};

} // namespace vw

#endif // ENTITY_H
