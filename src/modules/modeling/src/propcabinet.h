#ifndef PROPCABINET_H
#define PROPCABINET_H

#include <qtwidgets_ext/cabinet.h>
#include <ui_vw_editor/geometryeditor.h>

#include <vw/scene.h>

class PropCabinet: public Cabinet
{
    Q_OBJECT
public:
    PropCabinet(QWidget *parent = nullptr);
    ~PropCabinet();

public slots:
    void onCurrentEntityChanged(dream::Entity *entity);
    void onCurrentSceneChanged(dream::Scene *scene);

private:
    void init();
    void setCurrentEntity(dream::Entity *entity);

    GeometryEditor *geo_editor_;
    dream::Entity *current_entity_;
};

#endif // PROPCABINET_H
