#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vw/entity.h>
#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/grid.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vw::Entity *scene = new vw::Entity(this);
//    vw::Cube *cube = scene->addChild<vw::Cube>();
//    cube->setHeight(0.5f);
//    cube->setWidth(0.2f);
//    cube->setLength(0.2f);
//    scene->addChild<vw::Grid>();

//    vw::Cone *cone = scene->addChild<vw::Cone>();

    ui->centralwidget->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
