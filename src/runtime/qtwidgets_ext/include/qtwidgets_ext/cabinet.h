#ifndef CABINET_H
#define CABINET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>

#include "drawer.h"

class Cabinet : public QWidget
{
    Q_OBJECT
public:
    explicit Cabinet(QWidget *parent = nullptr);

    Drawer *addDrawer(const QString &name);
    void addDrawer(Drawer *drawer);
    void removeDrawer(Drawer *drawer);

    void foldAll();
    void expandAll();

signals:

public slots:

private:
    void init();

    QScrollArea *scroll_area_;
    QWidget *central_widget_;
    QVBoxLayout *drawer_layout_;
    QList<Drawer *> drawer_list_;
};

#endif // CABINET_H
