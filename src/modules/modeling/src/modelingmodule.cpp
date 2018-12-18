#include "modelingmodule.h"

#include <ui_vw_editor/geometryeditor.h>
#include <cradle/cradle.h>

ModelingModule::ModelingModule():
    create_panel_(nullptr),
    prop_panel_(nullptr)
{
    setObjectName("modeling");
    Cradle::addObject(this);
}

ModelingModule::~ModelingModule()
{
    Cradle::removeObject(this);

    if(create_panel_ != nullptr){
        delete create_panel_;
        create_panel_ = nullptr;
    }

    if(prop_panel_ != nullptr){
        delete prop_panel_;
        prop_panel_ = nullptr;
    }
}

QString ModelingModule::name()
{
    return tr("Modeling");
}

QWidget *ModelingModule::leftPanel()
{
    if(create_panel_ == nullptr){
        create_panel_ = new CreatePanel;
    }

    return create_panel_;
}

QWidget *ModelingModule::bottomPanel()
{
    return nullptr;
}

QWidget *ModelingModule::rightPanel()
{
    if(prop_panel_ == nullptr){
        prop_panel_ = new Cabinet;
        prop_panel_->addDrawer(new GeometryEditor);
    }

    return prop_panel_;
}
