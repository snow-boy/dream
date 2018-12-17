#ifndef SCENE_SIGNALS_H
#define SCENE_SIGNALS_H

#include <QObject>

#define SigSceneAdded SIGNAL(sigSceneAdded(IScene *))
#define SigSceneRemoved SIGNAL(sigSceneRemoved(IScene *))
#define SigCurrentSceneChanged SIGNAL(sigCurrentSceneChanged(IScene *))
#define SigEntityAdded SIGNAL(sigEntityAdded(IScene *, vw::Entity *))
#define SigEntityRemoved SIGNAL(sigEntityRemoved(IScene *, vw::Entity *))
#define SigCurrentEntityChanged SIGNAL(sigCurrentEntityChanged(IScene *, vw::Entity *))
#define SigEntitySelected SIGNAL(sigEntitySelected(IScene *, vw::Entity *))
#define SigEntityDeselected SIGNAL(sigEntityDeselected(IScene *, vw::Entity *))

#endif // SCENE_SIGNALS_H
