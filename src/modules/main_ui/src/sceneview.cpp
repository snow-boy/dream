#include "sceneview.h"
#include <QMouseEvent>
#define _USE_MATH_DEFINES
#include <math.h>

SceneView::SceneView(QWidget *parent) :
    QOpenGLWidget(parent),
    scene_(nullptr),
    env_render_(nullptr),
    geo_render_(nullptr),
    current_camera_(nullptr)
{
    current_camera_ = new vw::Camera(this);

    current_camera_->lookAt(QVector3D(-1, 1, 1), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
    current_camera_->perspective(60, 1, 1, 3);
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

    if(e->buttons() & Qt::MiddleButton){
        QMatrix4x4 m_y;
        QQuaternion q_y = QQuaternion::fromAxisAndAngle(0, 1, 0, diff_x/180*M_PI*10);
        m_y.rotate(q_y);
        world_y_rotation_matrix_ = world_y_rotation_matrix_ * m_y;

        QMatrix4x4 m_x;
        QMatrix4x4 camera_matrx = current_camera_->toMatrix();
        QVector3D axis = camera_matrx.inverted() * QVector3D(1, 0, 0) - camera_matrx.inverted() * QVector3D(0, 0, 0);
        QQuaternion q_x = QQuaternion::fromAxisAndAngle(axis, diff_y/180*M_PI*10);
        m_x.rotate(q_x);
        world_x_rotation_matrix_ = world_x_rotation_matrix_ * m_x;
    }
    else if(e->buttons() & Qt::RightButton){

    }

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

    QMatrix4x4 m = world_tranlation_matrix_ * world_y_rotation_matrix_;
    if(current_camera_ != nullptr){
        QMatrix4x4 camera_matrx = current_camera_->toMatrix();
        m = camera_matrx * world_x_rotation_matrix_ * m;
    }

    env_render_->updateWorldMatrix(m);
    geo_render_->updateWorldMatrix(m);

    env_render_->render();

    if(scene_ != nullptr){
        renderScene();
    }
}

void SceneView::renderScene()
{
    Q_ASSERT(scene_ != nullptr);

    Q_ASSERT(geo_render_ != nullptr);
    QList<vw::Geometry *> geo_list = scene_->findChildren<vw::Geometry*>();
    for(vw::Geometry *geo : geo_list){
        geo_render_->render(geo);
    }
}

