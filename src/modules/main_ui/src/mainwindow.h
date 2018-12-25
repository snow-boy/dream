#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStackedLayout>

#include <vw/scene.h>

#include "i_toolbox_view.h"


namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addToolboxView(IToolboxView *toolbox_view);
    void removeToolboxView(IToolboxView *toolbox_view);

public slots:
    void onCurrentSceneChanged(dream::Scene *scene);

private slots:
    void on_pushButton_save_layout_clicked();
    void setCurrentToolbox(int index);

private:
    void init();

    Ui::MainWindow *ui;
    QVector<IToolboxView *> toolbox_views_;
    QStackedLayout *left_panel_layout_;
    QStackedLayout *right_panel_layout_;
    QStackedLayout *bottom_panel_layout_;
};

#endif // MAINWINDOW_H
