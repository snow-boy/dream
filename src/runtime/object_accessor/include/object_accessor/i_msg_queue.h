#ifndef I_MSG_QUEUE_H
#define I_MSG_QUEUE_H

#include <functional>

class IMsgQueue
{
public:
    virtual ~IMsgQueue(){}
    virtual void queue(std::function<void ()> cmd) = 0;
    virtual void blockQueue(std::function<void ()> cmd) = 0;
};

#endif // I_MSG_QUEUE_H
