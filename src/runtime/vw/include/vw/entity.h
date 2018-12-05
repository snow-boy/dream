#ifndef ENTITY_H
#define ENTITY_H

#include "vw_global.h"

#include <memory>
#include <QObject>
#include <QList>
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

namespace vw {

class Component;

class VW_DECL Entity : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVector3D offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotaionChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)

public:
    Entity(QObject *parent = nullptr);
    ~Entity();

    void setPosition(const QVector3D &pos);
    QVector3D position() const;

    void setOffset(const QVector3D &offset);
    QVector3D offset() const;

    void setRotation(const QQuaternion &q);
    QQuaternion rotation() const;

    void setScale(const QVector3D &scale);
    QVector3D scale() const;

    void setPivot(const QMatrix4x4 &pivot);
    QMatrix4x4 pivot() const;

    void addComponent(Component *component);
    void removeComponent(Component *component);
    QList<Component *> components() const;

    template<typename T>
    T *addChild()
    {
        return new T(this);
    }

    template<typename T>
    T findComponent()
    {
        QList<Component *> component_list = components();
        for(Component *component : component_list){
            T t_component = qobject_cast<T>(component);
            if(t_component != nullptr){
                return t_component;
            }
        }
        return nullptr;
    }

    template<typename T>
    QList<T> findComponents()
    {
        QList<Component *> component_list = components();
        QList<T> t_component_list;
        for(Component *component : component_list){
            T t_component = qobject_cast<T>(component);
            if(t_component != nullptr){
                t_component_list.append(t_component);
            }
        }
        return t_component_list;
    }

signals:
    void offsetChanged(const QVector3D &pos);
    void positionChanged(const QVector3D &pos);
    void rotaionChanged(const QQuaternion &rot);
    void scaleChanged(const QVector3D &scale);

    void componentAdded(Component *component);
    void componentRemoved(Component *component);

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // ENTITY_H
