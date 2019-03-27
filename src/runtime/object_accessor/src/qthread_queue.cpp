#include "qthread_queue.h"
#include "tactorimp.h"

namespace  {
    TActorManager g_tactor_mgr;
}

QThreadQueue::QThreadQueue(QThread *thread)
{
    imp_ = g_tactor_mgr.getActor(thread);
}

void QThreadQueue::queue(std::function<void ()> cmd)
{
    imp_->postCmd(cmd);
}

void QThreadQueue::blockQueue(std::function<void ()> cmd)
{
    if(QThread::currentThread() == imp_->thread()){
        cmd();
    }
    else{
        imp_->sendCmd(cmd);
    }
}
