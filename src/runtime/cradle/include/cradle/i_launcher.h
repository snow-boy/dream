#ifndef I_LAUNCHER_H
#define I_LAUNCHER_H

#include <QObject>

class ILauncher
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
};

#define ILauncher_iid "snow.dream.ilauncher"
Q_DECLARE_INTERFACE(ILauncher, ILauncher_iid)

#endif // I_LAUNCHER_H
