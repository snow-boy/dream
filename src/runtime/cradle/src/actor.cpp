#include "actor.h"
#include "saferunevent.h"

Actor::Actor(QObject *parent) :
    QObject(parent)
{

}

bool Actor::event(QEvent *e)
{
    if(e->type() == SafeRunEvent::eventType()){
        static_cast<SafeRunEvent *>(e)->run();
        e->accept();
        return true;
    }

    return QObject::event(e);
}
