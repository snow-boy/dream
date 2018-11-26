#ifndef I_TOOLBOX_VIEW_H
#define I_TOOLBOX_VIEW_H

#include <QWidget>
#include <QString>

class IToolboxView
{
public:
    virtual QString name() = 0;

    virtual QWidget *leftPanel() = 0;
    virtual QWidget *bottomPanel() = 0;
    virtual QWidget *rightPanel() = 0;
};

#define IToolboxView_iid "snow.dream.itoolboxview"
Q_DECLARE_INTERFACE(IToolboxView, IToolboxView_iid)

#endif // I_TOOLBOX_VIEW_H
