#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <QEvent>

enum EventTypes
{
    Evt_None = QEvent::User + 1,

    // EntityEvent
    Evt_SceneAdded,
    Evt_SceneRemoved,
    Evt_SetCurrentScene,
    Evt_CurrentSceneChanged,
    Evt_SetCurrentEntity,
    Evt_CurrentEntityChanged,
    Evt_SelectEntity,
    Evt_EntitySelected,
    Evt_EntityDeselected,
    Evt_EntityAdded,
    Evt_EntityRemoved
};

#endif // EVENT_TYPES_H
