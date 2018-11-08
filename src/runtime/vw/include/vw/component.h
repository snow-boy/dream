#ifndef COMPONENT_H
#define COMPONENT_H

#include "vw_global.h"
#include <memory>
#include <QObject>
#include <QList>

namespace vw {

class Entity;

class VW_DECL Component : public QObject
{
    Q_OBJECT
public:
    Component(QObject *parent = nullptr);
    ~Component();

    void addToEntity(Entity *entity);
    void removeFromEntity(Entity *entity);

    QList<Entity *> entities();

signals:
    void addedToEntity(Entity *entity);
    void removedFromEntity(Entity *entity);

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // COMPONENT_H
