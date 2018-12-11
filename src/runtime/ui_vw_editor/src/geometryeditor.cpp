#include "geometryeditor.h"
#include "ui_geometryeditor.h"
#include <Eigen/Dense>
#include <eigen_qt/eulerangles.h>

GeometryEditor::GeometryEditor(QWidget *parent) :
    Drawer("Geometry", parent),
    ui(new Ui::GeometryEditor),
    geometry_(nullptr)
{
    QWidget *content_widget = new QWidget;
    setContentWidget(content_widget);
    ui->setupUi(content_widget);

    // position
    connect(ui->lineEdit_position_x, &QLineEdit::editingFinished, this, [=](){
        QVector3D position = geometry_->position();
        position[0] = ui->lineEdit_position_x->text().toFloat();
        geometry_->setPosition(position);
    });

    connect(ui->lineEdit_position_y, &QLineEdit::editingFinished, this, [=](){
        QVector3D position = geometry_->position();
        position[1] = ui->lineEdit_position_y->text().toFloat();
        geometry_->setPosition(position);
    });

    connect(ui->lineEdit_position_z, &QLineEdit::editingFinished, this, [=](){
        QVector3D position = geometry_->position();
        position[2] = ui->lineEdit_position_z->text().toFloat();
        geometry_->setPosition(position);
    });

    // rotation
    connect(ui->lineEdit_rotation_x, &QLineEdit::editingFinished, this, [=](){
        EulerAngles angles;
        angles.fromQtQ(geometry_->rotation());
        angles[0] = ui->lineEdit_rotation_x->text().toFloat();
        geometry_->setRotation(angles.toQtQ());
    });

    connect(ui->lineEdit_rotation_y, &QLineEdit::editingFinished, this, [=](){
        EulerAngles angles;
        angles.fromQtQ(geometry_->rotation());
        angles[1] = ui->lineEdit_rotation_y->text().toFloat();
        geometry_->setRotation(angles.toQtQ());
    });

    connect(ui->lineEdit_rotation_z, &QLineEdit::editingFinished, this, [=](){
        EulerAngles angles;
        angles.fromQtQ(geometry_->rotation());
        angles[2] = ui->lineEdit_rotation_z->text().toFloat();
        geometry_->setRotation(angles.toQtQ());
    });

    // scale
    connect(ui->lineEdit_scale_x, &QLineEdit::editingFinished, this, [=](){
        QVector3D scale = geometry_->scale();
        scale[0] = ui->lineEdit_scale_x->text().toFloat();
        geometry_->setScale(scale);
    });

    connect(ui->lineEdit_scale_y, &QLineEdit::editingFinished, this, [=](){
        QVector3D scale = geometry_->scale();
        scale[1] = ui->lineEdit_scale_y->text().toFloat();
        geometry_->setScale(scale);
    });

    connect(ui->lineEdit_scale_x, &QLineEdit::editingFinished, this, [=](){
        QVector3D scale = geometry_->scale();
        scale[2] = ui->lineEdit_scale_z->text().toFloat();
        geometry_->setScale(scale);
    });
}

GeometryEditor::~GeometryEditor()
{
    delete ui;
}

void GeometryEditor::setGemetry(vw::Geometry *geo)
{
    if(geo != nullptr){
        contentWidget()->setEnabled(true);
    }
    else{
        contentWidget()->setEnabled(false);
    }

    updateUi();
}

void GeometryEditor::updateUi()
{
    if(geometry_ != nullptr){
        QVector3D position = geometry_->position();
        ui->lineEdit_position_x->setText(QString::number(position.x()));
        ui->lineEdit_position_y->setText(QString::number(position.y()));
        ui->lineEdit_position_z->setText(QString::number(position.z()));

        EulerAngles angles;
        angles.fromQtQ(geometry_->rotation());
        ui->lineEdit_rotation_x->setText(QString::number(angles[0]));
        ui->lineEdit_rotation_y->setText(QString::number(angles[1]));
        ui->lineEdit_rotation_z->setText(QString::number(angles[2]));

        QVector3D scale = geometry_->scale();
        ui->lineEdit_scale_x->setText(QString::number(scale[0]));
        ui->lineEdit_scale_y->setText(QString::number(scale[1]));
        ui->lineEdit_scale_z->setText(QString::number(scale[2]));
    }
    else{
        ui->lineEdit_position_x->setText("-");
        ui->lineEdit_position_y->setText("-");
        ui->lineEdit_position_z->setText("-");

        ui->lineEdit_rotation_x->setText("-");
        ui->lineEdit_rotation_y->setText("-");
        ui->lineEdit_rotation_z->setText("-");

        ui->lineEdit_scale_x->setText("-");
        ui->lineEdit_scale_y->setText("-");
        ui->lineEdit_scale_z->setText("-");
    }
}
