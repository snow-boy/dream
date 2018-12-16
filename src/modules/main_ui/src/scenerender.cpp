#include "scenerender.h"
#include <QQuaternion>

#define MAX_PERSPECTIVE_ANGLE 160
#define MIN_PERSPECTIVE_ANGLE 1

SceneRender::SceneRender(QObject *parent) :
    QObject(parent),
    scene_(nullptr),
    env_render_(nullptr),
    geo_render_(nullptr),
    current_camera_(nullptr)
{
    world_scale_matrix_.scale(0.1f, 0.1f, 0.1f);

    axis_ = new vw::Axis(this);
    axis_->hideArray();
    default_world_camera_ = new vw::Camera(this);
    default_world_camera_->lookAt(QVector3D(-2, 2, 2), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
    default_world_camera_->perspective(30, 1, 1, 5);

    current_camera_ = default_world_camera_;

    axis_matrix_.ortho(-8, 8, -8, 8, -8, 8);
    axis_matrix_.lookAt(QVector3D(-2, 2, 2), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
}

void SceneRender::initialize()
{
    initializeOpenGLFunctions();

    env_render_ = new EnvRender(this);
    env_render_->initialize();

    geo_render_ = new GeometryRender(this);
    geo_render_->initialize();
}

void SceneRender::setScene(vw::Entity *scene)
{
    scene_ = scene;
}

void SceneRender::translate(const QVector2D &translation)
{
    QMatrix4x4 translation_matrix;
    translation_matrix.translate(QVector3D(translation.x(), translation.y(), 0));
    world_tranlation_matrix_ =  translation_matrix * world_tranlation_matrix_;
}

void SceneRender::rotate(const QVector2D &rotation)
{
    QMatrix4x4 m_y;
    QQuaternion q_y = QQuaternion::fromAxisAndAngle(0, 1, 0, rotation.x());
    m_y.rotate(q_y);
    world_y_rotation_matrix_ = world_y_rotation_matrix_ * m_y;

    QMatrix4x4 m_x;
    QMatrix4x4 camera_matrx = current_camera_->toMatrix().inverted();
    QVector3D axis = camera_matrx * QVector3D(1, 0, 0) - camera_matrx * QVector3D(0, 0, 0);
    QQuaternion q_x = QQuaternion::fromAxisAndAngle(axis, rotation.y());
    m_x.rotate(q_x);
    world_x_rotation_matrix_ = world_x_rotation_matrix_ * m_x;
}

void SceneRender::wheel(int delta)
{
    float factor = 1.0f - 0.1f*delta;

    float angle = current_camera_->verticalAngle()*factor;
    if(angle > MAX_PERSPECTIVE_ANGLE){
        angle = MAX_PERSPECTIVE_ANGLE;
    }

    if(angle < MIN_PERSPECTIVE_ANGLE){
        angle = MIN_PERSPECTIVE_ANGLE;
    }

    current_camera_->perspective(angle,
                                 current_camera_->aspectRatio(),
                                 current_camera_->nearPlane(),
                                 current_camera_->forPlane());
}

vw::Camera *SceneRender::currentCamera()
{
    return current_camera_;
}

void SceneRender::setCurrentCamera(vw::Camera *camera)
{
    if(camera != nullptr){
        current_camera_ = camera;
    }
    else{
        current_camera_ = default_world_camera_;
    }

}

void SceneRender::render()
{
    {
        glViewport(0, 0, viewport_.width(), viewport_.height());
        QMatrix4x4 m = world_scale_matrix_ *
                world_x_rotation_matrix_ *
                world_y_rotation_matrix_;

        if(current_camera_ != nullptr){
            QMatrix4x4 camera_matrx = current_camera_->toMatrix();
            m = world_tranlation_matrix_ * camera_matrx * m;
        }

        env_render_->updateWorldMatrix(m);
        geo_render_->updateWorldMatrix(m);

        env_render_->render();

        if(scene_ != nullptr){
            QList<vw::Geometry *> geo_list = scene_->findChildren<vw::Geometry*>();
            for(vw::Geometry *geo : geo_list){
                geo_render_->render(geo);
            }
        }
    }

    {
        glViewport(0, 0, 100, 100);

        QMatrix4x4 m =
                axis_matrix_ *
                world_x_rotation_matrix_ *
                world_y_rotation_matrix_;

        geo_render_->updateWorldMatrix(m);
        geo_render_->render(axis_);
        QList<vw::Geometry *> geo_list = axis_->findChildren<vw::Geometry*>();
        for(vw::Geometry *geo : geo_list){
            geo_render_->render(geo);
        }
    }
}

QMatrix4x4 SceneRender::rotationMatrix()
{
    return
        world_x_rotation_matrix_ *
            world_y_rotation_matrix_;
}

void SceneRender::setViewport(const QRect &view_port)
{
    viewport_ = view_port;

    current_camera_->perspective(current_camera_->verticalAngle(),
                                 static_cast<float>(viewport_.width())/viewport_.height(),
                                 current_camera_->nearPlane(),
                                 current_camera_->forPlane());
}
