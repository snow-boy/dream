#ifndef LIFE_H
#define LIFE_H

#include "life_global.h"
#include <QObject>

namespace dream
{

class LIFE_DECL Life: public QObject
{
    Q_OBJECT
public:
    Life();
};

} // namespace dream

#endif // LIFE_H
