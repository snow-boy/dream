#ifndef I_CRADLE_EVENT_H
#define I_CRADLE_EVENT_H

#include <QEvent>

class ICradleEvent : public QEvent
{
public:
    ICradleEvent(Type type):
        QEvent (type)
    {}

    virtual ICradleEvent *clone() = 0;
};

#endif // I_CRADLE_EVENT_H
