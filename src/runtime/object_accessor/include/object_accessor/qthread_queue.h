#ifndef QTHREAD_QUEUE_H
#define QTHREAD_QUEUE_H

#include <memory>

#include "object_accessor_global.h"
#include "i_msg_queue.h"

class QThread;
class TActorImp;

class OBJECT_ACCESSOR_DECL QThreadQueue: public IMsgQueue
{
public:
    QThreadQueue(QThread *thread);

    // IMsgQueue interface
    virtual void queue(std::function<void ()> cmd) override;
    virtual void blockQueue(std::function<void ()> cmd) override;

private:
    std::shared_ptr<TActorImp> imp_;
};

#endif // QTHREAD_QUEUE_H
