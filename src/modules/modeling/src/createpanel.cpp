#include "createpanel.h"
#include "ui_createpanel.h"

#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>
#include <cradle/cradle.h>

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

}

void CreatePanel::on_pushButton_create_cone_clicked()
{

}

void CreatePanel::on_pushButton_axis_clicked()
{

}
