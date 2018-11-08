#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vw/entity.h>
#include <vw/cube.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vw::Entity *scene = new vw::Entity(this);
    new vw::Cube(0.5, scene);

    ui->centralwidget->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
