#include "sceneview.h"
#include <QMouseEvent>
#define _USE_MATH_DEFINES
#include <math.h>

SceneView::SceneView(QWidget *parent) :
    QOpenGLWidget(parent),
    scene_(nullptr)
{

}

SceneView::~SceneView()
{
}

void SceneView::setScene(vw::Entity *scene)
{
    scene_ = scene;
    update();
}

void SceneView::mousePressEvent(QMouseEvent *e)
{
    last_pos_ = e->globalPos();
}

void SceneView::mouseMoveEvent(QMouseEvent *e)
{
    QPoint current_pos = e->globalPos();

    float diff_x = current_pos.x() - last_pos_.x();
    float diff_y = current_pos.y() - last_pos_.y();

    last_pos_ = current_pos;

    QQuaternion q_x = QQuaternion::fromAxisAndAngle(0, 1, 0, diff_x/360*M_PI*10);
    QQuaternion q_y = QQuaternion::fromAxisAndAngle(1, 0, 0, diff_y/360*M_PI*10);

    QMatrix4x4 m;
    m.rotate(q_y*q_x);
    current_matrix_ = current_matrix_ * current_matrix_.inverted() * m * current_matrix_;
    update();
}

void SceneView::initializeGL()
{
    bool ret = initializeOpenGLFunctions();
    Q_ASSERT(ret);
}

void SceneView::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void SceneView::drawGrid()
{

}
