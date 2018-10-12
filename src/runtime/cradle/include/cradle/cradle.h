#ifndef CRADLE_H
#define CRADLE_H

#include "cradle_global.h"
#include <QStringList>
#include <QObject>

class CRADLE_DECL Cradle
{
public:
    static void setModuleDir(const QStringList &dir_list);

    static void loadModules();

    static void unloadModules();

    static QObject *getModule(const QString &name);

    template<typename T>
    static T *getObject(const QString &module_name)
    {
        return qobject_cast<T *>(getModule(module_name));
    }

    static QList<QObject *> getModules(const QString &prefix);

    template<typename T>
    static QList<T *> getObjects(const QString &prefix)
    {
        QList<QObject *> module_list = getModules(prefix);
        QList<T *> object_list;
        for(QObject *module : module_list){
            if(T *obj = qobject_cast<T *>(module)){
                object_list.append(obj);
            }
            else{
                Q_ASSERT(false);
            }
        }

        return object_list;
    }
};

#endif // CRADLE_H