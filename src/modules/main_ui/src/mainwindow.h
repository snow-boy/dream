#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    void init();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
