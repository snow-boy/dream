#ifndef COMPONENT_H
#define COMPONENT_H

#include "vw_global.h"
#include <QObject>

namespace vw {

class VW_DECL Component : public QObject
{
    Q_OBJECT
public:
    Component();
};

} // namespace vw

#endif // COMPONENT_H
