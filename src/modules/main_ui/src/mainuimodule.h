#ifndef MAINUIMODULE_H
#define MAINUIMODULE_H

#include <QObject>
#include <cradle/i_launcher.h>
#include "mainwindow.h"

#define MAIN_UI_IID "dream.modules.main_ui"

class MainUIModule : public QObject,
        public ILauncher
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MAIN_UI_IID)
    Q_INTERFACES(ILauncher)

public:
    explicit MainUIModule(QObject *parent = nullptr);
    ~MainUIModule();

    // ILauncher interface
public:
    virtual void start() override;
    virtual void stop() override;

signals:

public slots:

private:
    MainWindow *main_window_;
};

#endif // MAINUIMODULE_H
