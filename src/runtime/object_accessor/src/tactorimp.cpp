#include "tactorimp.h"

TActorImp::TActorImp(QObject *parent) :
    QObject(parent)
{
    connect(this, &TActorImp::postCmd, this, &TActorImp::doCmd, Qt::QueuedConnection);
    connect(this, &TActorImp::sendCmd, this, &TActorImp::doCmd, Qt::BlockingQueuedConnection);
}

void TActorImp::doCmd(std::function<void ()> cmd)
{
    cmd();
}


std::shared_ptr<TActorImp> TActorManager::getActor(QThread *thread)
{
    QMutexLocker lg(&mutex_);

    std::shared_ptr<TActorImp> actor = nullptr;
    if(!thread_actor_map_.contains(thread)){
        actor = std::make_shared<TActorImp>();
        actor->moveToThread(thread);
        thread_actor_map_[thread] = actor;
        connect(thread, &QObject::destroyed, this, &TActorManager::onThreadDestoryed);
    }
    else{
        actor = thread_actor_map_[thread];
    }

    return actor;
}

void TActorManager::onThreadDestoryed(QObject *obj)
{
    QThread *thread = static_cast<QThread *>(obj);
    Q_ASSERT(thread != nullptr);

    QMutexLocker lg(&mutex_);
    if(thread_actor_map_.contains(thread)){
        thread_actor_map_.remove(thread);
    }
}
