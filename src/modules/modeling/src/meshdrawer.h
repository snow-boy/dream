#ifndef MESHDRAWER_H
#define MESHDRAWER_H

#include <QWidget>
#include <qtwidgets_ext/drawer.h>

class MeshDrawer : public Drawer
{
    Q_OBJECT

public:
    explicit MeshDrawer(QWidget *parent = nullptr);
    ~MeshDrawer();

private:
    void init();

    QWidget *content_widget_;
};

#endif // MESHDRAWER_H
