#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QVBoxLayout>
#include "i_toolbox_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addToolboxView(IToolboxView *toolbox_view);
    void removeToolboxView(IToolboxView *toolbox_view);

private slots:
    void on_pushButton_save_layout_clicked();
    void setCurrentToolbox(int index);

private:
    void init();

    Ui::MainWindow *ui;
    QVector<IToolboxView *> toolbox_views_;
    IToolboxView *current_toolbox_;
    QVBoxLayout *left_panel_layout_;
    QVBoxLayout *right_panel_layout_;
    QVBoxLayout *bottom_panel_layout_;
};

#endif // MAINWINDOW_H
