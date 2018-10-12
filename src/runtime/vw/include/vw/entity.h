#ifndef ENTITY_H
#define ENTITY_H

#include "vw_global.h"

#include <memory>
#include <QObject>
#include <QList>
#include <QVector3D>
#include <QQuaternion>

namespace vw {

class Component;

class VW_DECL Entity : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotaionChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)

public:
    Entity();
    ~Entity();

    void setPosition(const QVector3D &pos);
    QVector3D position() const;

    void setRotation(const QQuaternion &q);
    QQuaternion rotation() const;

    void setScale(const QVector3D &scale);
    QVector3D scale() const;

    Entity *parent() const;
    void addChild(Entity *entity);
    void removeChild(Entity *entity);
    QList<Entity *> entities() const;

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);
    QList<std::shared_ptr<Component>> components() const;

signals:
    void positionChanged(const QVector3D &pos);
    void rotaionChanged(const QQuaternion &rot);
    void scaleChanged(const QVector3D &scale);

    void childAdded(Entity *child);
    void childRemoved(Entity *child);

    void componentAdded(std::shared_ptr<Component> component);
    void componentRemoved(std::shared_ptr<Component> component);

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // ENTITY_H
