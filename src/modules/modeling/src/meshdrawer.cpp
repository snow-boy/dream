#include "meshdrawer.h"
#include <QVBoxLayout>
#include <QMap>
#include <QPushButton>
#include <functional>

#include <vw/cube.h>
#include <vw/axis.h>
#include <vw/cone.h>
#include <vw/life.h>
#include <cradle/cradle.h>
#include <vw/scene.h>

MeshDrawer::MeshDrawer(QWidget *parent) :
    Drawer(tr("Mesh"), parent)
{
    init();
}

MeshDrawer::~MeshDrawer()
{
}

void MeshDrawer::init()
{
    setName(tr("Mesh"));

    QVBoxLayout *layout = new QVBoxLayout;
    content_widget_ = new QWidget;
    content_widget_->setLayout(layout);
    layout->setMargin(0);
    layout->setSpacing(1);
    setContentWidget(content_widget_);

    QMap<QString, std::function<dream::Entity *()>> name_builder =
    {

    {
       tr("cube"),
       [](){ return new dream::Cube; }
    },

    {
       tr("cone"),
       [](){ return new dream::Cone; }
    },

    {
       tr("axis"),
       [](){ return new dream::Axis; }
    }

    };

    for(QString &key : name_builder.keys()){
        QPushButton *button = new QPushButton(key);
        auto builder = name_builder[key];
        connect(button, &QPushButton::clicked, [=](){
            dream::Scene *scene = Cradle::findObject<dream::Life *>()->currentScene();
            Q_ASSERT(scene != nullptr);
            dream::Entity *entity = builder();
            entity->setObjectName(key);
            scene->addEntity(entity);
        });
        layout->addWidget(button);
    }

    if(Cradle::findObject<dream::Life *>()->currentScene() != nullptr){
        setEnabled(true);
    }
    else{
        setDisabled(true);
    }
}
