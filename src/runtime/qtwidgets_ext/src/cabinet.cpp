#include "cabinet.h"
#include <QLabel>
#include <QSpacerItem>

Cabinet::Cabinet(QWidget *parent) :
    QWidget(parent)
{
    init();
}

Drawer *Cabinet::addDrawer(const QString &name)
{
    Drawer *drawer = new Drawer(name);
    addDrawer(drawer);
    return drawer;
}

void Cabinet::addDrawer(Drawer *drawer)
{
    drawer_layout_->insertWidget(drawer_layout_->count() - 1, drawer);
    drawer_list_.append(drawer);
}

void Cabinet::removeDrawer(Drawer *drawer)
{
    drawer_layout_->removeWidget(drawer);
    drawer->setParent(nullptr);
}

void Cabinet::foldAll()
{
    for(Drawer *drawer : drawer_list_){
        drawer->fold();
    }
}

void Cabinet::expandAll()
{
    for(Drawer *drawer : drawer_list_){
        drawer->expand();
    }
}

void Cabinet::init()
{
    {
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(0);
        scroll_area_ = new QScrollArea(this);
        scroll_area_->setWidgetResizable(true);
        layout->addWidget(scroll_area_);
        setLayout(layout);
    }

    {
        central_widget_ = new QWidget;
        drawer_layout_ = new QVBoxLayout;
        drawer_layout_->setMargin(0);
        drawer_layout_->setSpacing(0);
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        drawer_layout_->addSpacerItem(spacer);
        central_widget_->setLayout(drawer_layout_);
        scroll_area_->setWidget(central_widget_);
    }
}
