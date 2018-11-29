#include "modelingmodule.h"

ModelingModule::ModelingModule():
    left_panel_(nullptr)
{

}

ModelingModule::~ModelingModule()
{
    if(left_panel_ != nullptr){
        delete left_panel_;
        left_panel_ = nullptr;
    }
}

QString ModelingModule::name()
{
    return tr("Modeling");
}

QWidget *ModelingModule::leftPanel()
{
    if(left_panel_ == nullptr){
        left_panel_ = new CreatePanel;
    }

    return left_panel_;
}

QWidget *ModelingModule::bottomPanel()
{
    return nullptr;
}

QWidget *ModelingModule::rightPanel()
{
    return nullptr;
}
