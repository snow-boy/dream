#ifndef CRADLE_H
#define CRADLE_H

#include "cradle_global.h"
#include <QStringList>
#include <QObject>
#include <memory>
#include <functional>

class CRADLE_DECL Cradle
{
public:
    static void setModuleDir(const QStringList &dir_list);
    static void loadModules();
    static void unloadModules();

    static void addObject(QObject *obj);
    static void removeObject(QObject *obj);

    template<typename T>
    static T findObject(const QString &name = QString())
    {
        QList<T> object_list = findObjects<T>(name);
        if(object_list.size() > 0){
            return object_list.first();
        }
        return nullptr;
    }

    template<typename T>
    static QList<T> findObjects(const QString &name = QString())
    {
        QList<QObject *> object_list = findObjectsByName(name);
        QList<T> object_t_list;
        for(QObject *obj : object_list){
            T t = qobject_cast<T>(obj);
            if(t != nullptr){
                object_t_list.append(t);
            }
        }

        return object_t_list;
    }

    static void registerSignaler(QObject *signaler);
    static void unregisterSignaler(QObject *signaler);
    static void installSignalAlias(QObject *signaler, const char *signal, const char *alias);

    static void registerSloter(QObject *sloter, const char *signal, const char *slot);
    static void unregisterSloter(QObject *sloter, const char *signal, const char *slot);
    static void unregisterSloter(QObject *sloter);

    static void threadSafeRun(QObject *context, const std::function<void ()> &runner);

private:
    static QList<QObject *> findObjectsByName(const QString &name);
};

#define SigObjectAdded SIGNAL(objectAdded(QObject *))
#define SigObjectRemoved SIGNAL(objectRemoved(QObject *))

#define ThreadSafeCall(obj, fun)\
    Cradle::threadSafeRun(obj, [=](){obj->fun;})

#endif // CRADLE_H
