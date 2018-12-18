#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <QWidget>
#include <qtwidgets_ext/drawer.h>
#include <vw/geometry.h>

namespace Ui {
class GeometryEditor;
}

class GeometryEditor : public Drawer
{
    Q_OBJECT

public:
    explicit GeometryEditor(QWidget *parent = nullptr);
    ~GeometryEditor();

    void setGemetry(dream::Geometry *geo);
    void updateUi();

private:
    void postUpdateEvent();

    Ui::GeometryEditor *ui;
    dream::Geometry *geometry_;
};

#endif // GEOMETRYEDITOR_H
