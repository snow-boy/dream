#include "createpanel.h"
#include "ui_createpanel.h"

#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>
#include <cradle/cradle.h>
#include <life/scene_signals.h>

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

    Cradle::registerSloter(this, SigCurrentSceneChanged, SLOT(currentSceneChanged(IScene *)));
}

CreatePanel::~CreatePanel()
{
    Cradle::unregisterSloter(this, SigCurrentSceneChanged, SLOT(currentSceneChanged(IScene *)));
    delete ui;
}

void CreatePanel::currentSceneChanged(IScene *current_scene)
{
    current_scene_ = current_scene;
    if(current_scene_ != nullptr){
        setEnabled(true);
    }
    else{
        setDisabled(true);
    }
}

void CreatePanel::on_pushButton_create_cube_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    current_scene_->addEntity<vw::Cube>();
}

void CreatePanel::on_pushButton_create_cone_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    current_scene_->addEntity<vw::Cone>();
}

void CreatePanel::on_pushButton_axis_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    current_scene_->addEntity<vw::Axis>();
}
