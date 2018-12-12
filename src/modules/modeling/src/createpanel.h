#ifndef CREATEPANEL_H
#define CREATEPANEL_H

#include <QWidget>
#include <vw/entity.h>

namespace Ui {
class CreatePanel;
}

class CreatePanel : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePanel(QWidget *parent = nullptr);
    ~CreatePanel();

    // QObject interface
    virtual bool event(QEvent *e) override;

private slots:
    void on_pushButton_create_cube_clicked();

    void on_pushButton_create_cone_clicked();

    void on_pushButton_axis_clicked();

private:
    Ui::CreatePanel *ui;
    vw::Entity *current_scene_;
};

#endif // CREATEPANEL_H
