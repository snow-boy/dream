#include "mainuimodule.h"

#include <QApplication>
#include <QFile>
#include <QString>

MainUIModule::MainUIModule(QObject *parent) :
    QObject(parent)
{
    main_window_ = new MainWindow;
}

MainUIModule::~MainUIModule()
{
    delete main_window_;
    main_window_ = nullptr;
}

void MainUIModule::start()
{
//    {
//        QFile file("://stylesheets/material-blue.qss");
//        file.open(QIODevice::ReadOnly);
//        QString stylesheet(file.readAll().data());
//        qApp->setStyleSheet(stylesheet);
//    }

    {
        IToolboxView *modeling = Cradle::getObject<IToolboxView>("modeling");
        main_window_->addToolboxView(modeling);
        toolbox_view_list_.append(modeling);
    }

    main_window_->show();
}

void MainUIModule::stop()
{
    for(IToolboxView * toolbox_view : toolbox_view_list_){
        main_window_->removeToolboxView(toolbox_view);
    }
}
