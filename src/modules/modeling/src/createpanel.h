#ifndef CREATEPANEL_H
#define CREATEPANEL_H

#include <QWidget>

namespace Ui {
class CreatePanel;
}

class CreatePanel : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePanel(QWidget *parent = nullptr);
    ~CreatePanel();

private slots:
    void on_pushButton_create_cube_clicked();

    void on_pushButton_create_cone_clicked();

    void on_pushButton_axis_clicked();

private:
    Ui::CreatePanel *ui;
};

#endif // CREATEPANEL_H
