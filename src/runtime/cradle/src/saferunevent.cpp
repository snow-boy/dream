#include "saferunevent.h"

SafeRunEvent::SafeRunEvent(const std::function<void ()> &runner):
    QEvent (SafeRunEvent::eventType()),
    runner_(runner)
{

}

QEvent::Type SafeRunEvent::eventType()
{
    static int type = -1;
    if(type < 0){
        type = registerEventType();
    }

    return static_cast<Type>(type);
}
