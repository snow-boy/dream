#include "actormanager.h"
#include <qcoreapplication.h>
#include <QMutexLocker>
#include <QThread>
#include "saferunevent.h"

ActorManager::ActorManager(QObject *parent) :
    QObject(parent)
{

}

ActorManager::~ActorManager()
{
    for(Actor *actor : thread_actor_map_.values()){
        delete actor;
    }
    thread_actor_map_.clear();
}

void ActorManager::safeRun(QObject *context, const std::function<void ()> &runner)
{
    if(QThread::currentThread() == context->thread()){
        runner();
        return;
    }

    {
        QMutexLocker lg(&mutex_);

        Actor *actor = nullptr;
        if(!thread_actor_map_.contains(context->thread())){
            actor = new Actor;
            actor->moveToThread(context->thread());
            thread_actor_map_[context->thread()] = actor;
            connect(context->thread(), &QObject::destroyed, this, &ActorManager::onThreadDestoryed);
        }

        qApp->postEvent(actor, new SafeRunEvent(runner));
    }
}

void ActorManager::onThreadDestoryed(QObject *obj)
{
    QThread *thread = qobject_cast<QThread *>(obj);
    Q_ASSERT(thread != nullptr);

    QMutexLocker lg(&mutex_);
    if(thread_actor_map_.contains(thread)){
        delete thread_actor_map_[thread];
        thread_actor_map_.remove(thread);
    }
}
