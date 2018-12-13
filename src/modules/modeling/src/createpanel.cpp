#include "createpanel.h"
#include "ui_createpanel.h"

#include <vw/cube.h>
#include <vw/cone.h>
#include <vw/axis.h>
#include <cradle/cradle.h>
#include <life/i_scene_manager.h>
#include <events/events.h>

CreatePanel::CreatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatePanel)
{
    ui->setupUi(this);

    Cradle::registerEventHandler(this);

    ISceneManager *scene_manager = Cradle::getObject<ISceneManager>("life");
    current_scene_ = scene_manager->currentScene();
    if(current_scene_ == nullptr){
        setDisabled(true);
    }
}

CreatePanel::~CreatePanel()
{
    Cradle::unregisterEventHandler(this);

    delete ui;
}

bool CreatePanel::event(QEvent *e)
{
    if(e->type() == static_cast<QEvent::Type>(Evt_CurrentSceneChanged)){
        EntityEvent *entity_event = static_cast<EntityEvent *>(e);
        current_scene_ = entity_event->entity();
        if(current_scene_ == nullptr){
            setDisabled(true);
        }
        else{
            setEnabled(true);
        }
        e->accept();

        return true;
    }

    return QWidget::event(e);
}

void CreatePanel::on_pushButton_create_cube_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Cube *cube = current_scene_->addChild<vw::Cube>();
    EntityEvent event(Evt_EntityAdded, cube);
    Cradle::postEvent(&event, this);
}

void CreatePanel::on_pushButton_create_cone_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Cone *cone = current_scene_->addChild<vw::Cone>();
    EntityEvent event(Evt_EntityAdded, cone);
    Cradle::postEvent(&event, this);
}

void CreatePanel::on_pushButton_axis_clicked()
{
    Q_ASSERT(current_scene_ != nullptr);
    vw::Axis *axis = current_scene_->addChild<vw::Axis>();
    EntityEvent event(Evt_EntityAdded, axis);
    Cradle::postEvent(&event, this);
}
