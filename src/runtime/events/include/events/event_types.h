#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <QEvent>

enum EventTypes
{
    Evt_None = QEvent::User + 1,

    // EntityEvent
    Evt_SceneAdded,
    Evt_SceneRemoved,
    Evt_CurrentSceneChanged,
    Evt_CurrentEntityChanged,
    Evt_EntitySelected,
    Evt_EntityDeselected,
    Evt_EntityAdded,
    Evt_EntityRemoved,
    Evt_EntityPropChanged
};

#endif // EVENT_TYPES_H
