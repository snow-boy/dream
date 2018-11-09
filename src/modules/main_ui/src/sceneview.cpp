#include "sceneview.h"
#include <QMouseEvent>
#define _USE_MATH_DEFINES
#include <math.h>

SceneView::SceneView(QWidget *parent) :
    QOpenGLWidget(parent),
    scene_(nullptr),
    env_render_(nullptr),
    geo_render_(nullptr)
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

    QMatrix4x4 m;

    if(e->buttons() & Qt::LeftButton){
        QQuaternion q_x = QQuaternion::fromAxisAndAngle(0, 1, 0, diff_x/180*M_PI*10);
        QQuaternion q_y = QQuaternion::fromAxisAndAngle(1, 0, 0, diff_y/180*M_PI*10);
        m.rotate(q_y*q_x);
    }
    else if(e->buttons() & Qt::MiddleButton){
        m.translate(QVector3D(diff_x/width(), -diff_y/height(), 0));
    }
    else if(e->buttons() & Qt::RightButton){

    }

    current_matrix_ = m * current_matrix_;
    update();
}

void SceneView::initializeGL()
{
    bool ret = initializeOpenGLFunctions();
    Q_ASSERT(ret);

    env_render_ = new EnvRender(this);
    env_render_->initialize();

    geo_render_ = new GeometryRender(this);
    geo_render_->initialize();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(46.0f/255.0f, 47.0f/255.0f, 48.0f/255.0f, 1);
}

void SceneView::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    env_render_->updateWorldMatrix(current_matrix_);
    env_render_->render();

    if(scene_ != nullptr){
        renderScene();
    }
}

void SceneView::renderScene()
{
    Q_ASSERT(scene_ != nullptr);
    geo_render_->updateWorldMatrix(current_matrix_);

    Q_ASSERT(geo_render_ != nullptr);
    QList<vw::Geometry *> geo_list = scene_->findChildren<vw::Geometry*>();
    for(vw::Geometry *geo : geo_list){
        geo_render_->render(geo);
    }
}

