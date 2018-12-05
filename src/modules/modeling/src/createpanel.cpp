#include "createpanel.h"
#include "ui_createpanel.h"

#include <life/life.h>
#include <vw/entity.h>
#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>

CreatePanel::CreatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatePanel)
{
    ui->setupUi(this);
}

CreatePanel::~CreatePanel()
{
    delete ui;
}

void CreatePanel::on_pushButton_create_cube_clicked()
{
    Life::get()->currentScene()->addChild<vw::Cube>();
}

void CreatePanel::on_pushButton_create_cone_clicked()
{
    Life::get()->currentScene()->addChild<vw::Cone>();
}

void CreatePanel::on_pushButton_axis_clicked()
{
    Life::get()->currentScene()->addChild<vw::Axis>();
}
