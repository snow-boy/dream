#include "sceneview.h"
#include <QMouseEvent>
#include <QWheelEvent>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_PERSPECTIVE_ANGLE 160
#define MIN_PERSPECTIVE_ANGLE 1

SceneView::SceneView(QWidget *parent) :
    QOpenGLWidget(parent),
    scene_render_(nullptr)
{
    scene_render_ = new SceneRender;
}

SceneView::~SceneView()
{
    if(scene_render_ != nullptr){
        delete scene_render_;
        scene_render_ = nullptr;
    }
}

void SceneView::setScene(dream::Entity *scene)
{
    scene_render_->setScene(scene);
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

    if(e->buttons() & Qt::MiddleButton){
        if(e->modifiers() & Qt::SHIFT){
            scene_render_->translate(QVector2D(diff_x/width()*2, -diff_y/height()*2));
        }
        else{
            scene_render_->rotate(QVector2D(diff_x/180*M_PI*10, diff_y/180*M_PI*10));
        }
    }
    else if(e->buttons() & Qt::RightButton){

    }

    update();
}

void SceneView::wheelEvent(QWheelEvent *e)
{
    int delta = e->angleDelta().y() / 120;
    scene_render_->wheel(delta);

    update();
}

void SceneView::initializeGL()
{
    scene_render_->initialize();
}

void SceneView::resizeGL(int /*w*/, int /*h*/)
{
    scene_render_->setViewport(rect());
}

void SceneView::paintGL()
{
    scene_render_->render();
}

