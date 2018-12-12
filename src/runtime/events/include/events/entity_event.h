#ifndef SCENE_EVENT_H
#define SCENE_EVENT_H

#include <QSharedPointer>
#include <cradle/i_cradle_event.h>
#include <vw/entity.h>
#include "event_types.h"

class EntityEvent : public ICradleEvent
{
public:
    EntityEvent(EventTypes type, vw::Entity *entity):
        ICradleEvent (static_cast<Type>(type)),
        entity_(entity, [](vw::Entity *){})
    {}

    EntityEvent(EventTypes type, QSharedPointer<vw::Entity> entity):
        ICradleEvent (static_cast<Type>(type)),
        entity_(entity)
    {}

    // ICradleEvent interface
    virtual ICradleEvent *clone() override
    {
        EntityEvent *evt = new EntityEvent(static_cast<EventTypes>(type()), entity_);
        return evt;
    }

    vw::Entity *entity()
    {
        return entity_.data();
    }

private:
    QSharedPointer<vw::Entity> entity_;
};

#endif // SCENE_EVENT_H
