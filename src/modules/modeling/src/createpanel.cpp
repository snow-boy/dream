#include "createpanel.h"
#include "ui_createpanel.h"

#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>
#include <cradle/cradle.h>
#include <life/i_scene_manager.h>

CreatePanel::CreatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatePanel)
{
    ui->setupUi(this);

    ISceneManager *scene_manager = Cradle::getObject<ISceneManager>("life");
    current_scene_ = scene_manager->currentScene();
    if(current_scene_ == nullptr){
        setDisabled(true);
    }
}

CreatePanel::~CreatePanel()
{
    delete ui;
}

void CreatePanel::on_pushButton_create_cube_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Cube *cube = current_scene_->addChild<vw::Cube>();
}

void CreatePanel::on_pushButton_create_cone_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Cone *cone = current_scene_->addChild<vw::Cone>();
}

void CreatePanel::on_pushButton_axis_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Axis *axis = current_scene_->addChild<vw::Axis>();
}
