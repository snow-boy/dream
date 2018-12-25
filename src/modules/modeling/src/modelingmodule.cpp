#include "modelingmodule.h"

#include <ui_vw_editor/geometryeditor.h>
#include <cradle/cradle.h>

#include "propcabinet.h"

ModelingModule::ModelingModule():
    model_panel_(nullptr),
    prop_panel_(nullptr)
{
    setObjectName("modeling");
    Cradle::addObject(this);
}

ModelingModule::~ModelingModule()
{
    Cradle::removeObject(this);

    if(model_panel_ != nullptr){
        delete model_panel_;
        model_panel_ = nullptr;
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
    if(model_panel_ == nullptr){
        model_panel_ = new ModelCabinet;
    }

    return model_panel_;
}

QWidget *ModelingModule::bottomPanel()
{
    return nullptr;
}

QWidget *ModelingModule::rightPanel()
{
    if(prop_panel_ == nullptr){
        prop_panel_ = new PropCabinet;
    }

    return prop_panel_;
}
