#ifndef MODELINGMODULE_H
#define MODELINGMODULE_H

#include <QObject>
#include <QLabel>

#include <cradle/i_launcher.h>
#include <main_ui/i_toolbox_view.h>
#include <qtwidgets_ext/cabinet.h>

#include "createpanel.h"

#define MODELING_IID "dream.modules.modeling"

class ModelingModule: public QObject, public IToolboxView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MODELING_IID)
    Q_INTERFACES(IToolboxView)

public:
    ModelingModule();
    ~ModelingModule();

    // IToolboxView interface
    virtual QString name() override;
    virtual QWidget *leftPanel() override;
    virtual QWidget *bottomPanel() override;
    virtual QWidget *rightPanel() override;

private:
    CreatePanel *create_panel_;
    Cabinet *prop_panel_;
};

#endif // MODELINGMODULE_H
