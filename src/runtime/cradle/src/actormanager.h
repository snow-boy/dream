#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <QObject>
#include <QMap>
#include <functional>
#include <QMutex>
#include "actor.h"

class ActorManager : public QObject
{
    Q_OBJECT
public:
    explicit ActorManager(QObject *parent = nullptr);
    ~ActorManager();

    void safeRun(QObject *context, const std::function<void ()> &runner);

signals:

public slots:
    void onThreadDestoryed(QObject *obj);

private:
    QMap<QThread *, Actor *> thread_actor_map_;
    QMutex mutex_;
};

#endif // ACTORMANAGER_H
