#include "mainuimodule.h"

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
    main_window_->show();
}

void MainUIModule::stop()
{

}
