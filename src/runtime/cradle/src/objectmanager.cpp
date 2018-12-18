#include "objectmanager.h"

ObjectManager::ObjectManager(QObject *parent) :
    QObject(parent)
{

}

void ObjectManager::addObject(QObject *obj)
{
    Q_ASSERT(!object_list_.contains(obj));
    object_list_.append(obj);
    name_object_list_[obj->objectName()].append(obj);
    connect(obj, &QObject::objectNameChanged, this, &ObjectManager::onObjectNameChanged);

    emit objectAdded(obj);
}

void ObjectManager::removeObject(QObject *obj)
{
    Q_ASSERT(object_list_.contains(obj));
    Q_ASSERT(name_object_list_.contains(obj->objectName()));
    object_list_.removeOne(obj);
    name_object_list_[obj->objectName()].removeOne(obj);
    disconnect(obj, &QObject::objectNameChanged, this, &ObjectManager::onObjectNameChanged);

    emit objectRemoved(obj);
}

QList<QObject *> ObjectManager::findObjects(const QString &name)
{
    if(name.isEmpty()){
        return object_list_;
    }

    QList<QObject *> obj_list;

    if(name_object_list_.contains(name)){
        obj_list = name_object_list_[name];
    }

    return obj_list;
}

void ObjectManager::onObjectNameChanged(const QString &name)
{
    QObject *obj = sender();
    for(auto it = name_object_list_.begin(); it != name_object_list_.end(); ++it){
        if(it.value().contains(obj)){
            it.value().removeOne(obj);
            break;
        }
    }

    name_object_list_[name].append(obj);
}
