#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

#include <vw/entity.h>
#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/grid.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    vw::Entity *scene = new vw::Entity(this);
    //    vw::Cube *cube = scene->addChild<vw::Cube>();
    //    cube->setHeight(0.5f);
    //    cube->setWidth(0.2f);
    //    cube->setLength(0.2f);
    //    scene->addChild<vw::Grid>();

    //    vw::Cone *cone = scene->addChild<vw::Cone>();

    ui->widget_scene_view->setScene(scene);

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\main_splitter.dat)");
        file.open(QIODevice::ReadOnly);
        ui->splitter_main_vertical->restoreState(file.readAll());
    }

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\central_splitter.dat)");
        file.open(QIODevice::ReadOnly);
        ui->splitter_central_horizon->restoreState(file.readAll());
    }

    ui->widget_left_panel->hide();
}

void MainWindow::on_pushButton_save_layout_clicked()
{
    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\main_splitter.dat)");
        file.open(QIODevice::WriteOnly);
        file.write(ui->splitter_main_vertical->saveState());
    }

    {
        QFile file(R"(E:\develop\my_projects\dream\src\modules\main_ui\src\layout\init\central_splitter.dat)");
        file.open(QIODevice::WriteOnly);
        file.write(ui->splitter_central_horizon->saveState());
    }
}
