#ifndef MODELCABINET_H
#define MODELCABINET_H

#include <QWidget>
#include <qtwidgets_ext/cabinet.h>

#include "vw/scene.h"

class ModelCabinet : public Cabinet
{
    Q_OBJECT

public:
    explicit ModelCabinet(QWidget *parent = nullptr);
    ~ModelCabinet();

public slots:
    void onCurrentSceneChanged(dream::Scene *scene);

private:
    void init();
};

#endif // MODELCABINET_H
