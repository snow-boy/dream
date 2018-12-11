#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <QEvent>

enum EventTypes
{
    Evt_None = QEvent::User + 1,
    Evt_SetCurrentScene,
    Evt_CurrentSceneChanged,
    Evt_SetCurrentObject,
    Evt_CurrentObjectChanged
};

#endif // EVENT_TYPES_H
