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

    template<typename _InterfaceT>
    static _InterfaceT *getModuleI(const QString &name)
    {
        return qobject_cast<_InterfaceT *>(getModule(name));
    }
};

#endif // CRADLE_H
