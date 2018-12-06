#include "sceneview.h"
#include <QMouseEvent>
#include <QWheelEvent>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_PERSPECTIVE_ANGLE 160
#define MIN_PERSPECTIVE_ANGLE 1

SceneView::SceneView(QWidget *parent) :
    QOpenGLWidget(parent),
    current_camera_(nullptr),
    scene_render_(nullptr)
{
    current_camera_ = new vw::Camera(this);
    current_camera_->lookAt(QVector3D(-2, 2, 2), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
    current_camera_->perspective(30, 1, 1, 5);

    scene_render_ = new SceneRender(this);
    scene_render_->setCurrentCamera(current_camera_);
}

SceneView::~SceneView()
{
}

void SceneView::setScene(vw::Entity *scene)
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
    bool ret = initializeOpenGLFunctions();
    Q_ASSERT(ret);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(46.0f/255.0f, 47.0f/255.0f, 48.0f/255.0f, 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    scene_render_->initialize();
}

void SceneView::resizeGL(int w, int h)
{
    current_camera_->perspective(current_camera_->verticalAngle(),
                                 static_cast<float>(w)/h,
                                 current_camera_->nearPlane(),
                                 current_camera_->forPlane());
}

void SceneView::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    scene_render_->render();
}

