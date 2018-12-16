#include "modelingmodule.h"

#include <ui_vw_editor/geometryeditor.h>
#include "propertypanel.h"

ModelingModule::ModelingModule():
    create_panel_(nullptr),
    prop_panel_(nullptr)
{

}

ModelingModule::~ModelingModule()
{
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
        prop_panel_ = new PropertyPanel;
        prop_panel_->addDrawer(new GeometryEditor);
    }

    return prop_panel_;
}
