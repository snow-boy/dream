#include "scenerender.h"
#include <QQuaternion>

#include "envrender.h"
#include "geometryrender.h"

#define MAX_PERSPECTIVE_ANGLE 160
#define MIN_PERSPECTIVE_ANGLE 1

class SceneRender::Imp
{
public:
    Imp():
        scene_(nullptr),
        env_render_(nullptr),
        geo_render_(nullptr),
        default_world_camera_(nullptr),
        current_camera_(nullptr),
        axis_(nullptr)
    {}

    dream::Entity *scene_;

    QMatrix4x4 world_y_rotation_matrix_;
    QMatrix4x4 world_x_rotation_matrix_;
    QMatrix4x4 world_tranlation_matrix_;
    QMatrix4x4 world_scale_matrix_;

    EnvRender *env_render_;
    GeometryRender *geo_render_;
    dream::Camera *default_world_camera_;
    dream::Camera *current_camera_;
    QRect viewport_;

    QMatrix4x4 axis_matrix_;
    dream::Axis *axis_;
};

SceneRender::SceneRender(QObject *parent) :
    QObject(parent)
{
    imp_ = std::make_unique<Imp>();

    imp_->world_scale_matrix_.scale(0.1f, 0.1f, 0.1f);

    imp_->axis_ = new dream::Axis(this);
    imp_->axis_->hideArray();
    imp_->default_world_camera_ = new dream::Camera(this);
    imp_->default_world_camera_->lookAt(QVector3D(-2, 2, 2), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
    imp_->default_world_camera_->perspective(30, 1, 1, 5);

    imp_->current_camera_ = imp_->default_world_camera_;

    imp_->axis_matrix_.ortho(-8, 8, -8, 8, -8, 8);
    imp_->axis_matrix_.lookAt(QVector3D(-2, 2, 2), QVector3D(0, 0, 0), QVector3D(1, 1, -1));
}

SceneRender::~SceneRender()
{

}

void SceneRender::initialize()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(46.0f/255.0f, 47.0f/255.0f, 48.0f/255.0f, 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    imp_->env_render_ = new EnvRender(this);
    imp_->env_render_->initialize();

    imp_->geo_render_ = new GeometryRender(this);
    imp_->geo_render_->initialize();
}

void SceneRender::setScene(dream::Entity *scene)
{
    imp_->scene_ = scene;
}

void SceneRender::translate(const QVector2D &translation)
{
    QMatrix4x4 translation_matrix;
    translation_matrix.translate(QVector3D(translation.x(), translation.y(), 0));
    imp_->world_tranlation_matrix_ =  translation_matrix * imp_->world_tranlation_matrix_;
}

void SceneRender::rotate(const QVector2D &rotation)
{
    QMatrix4x4 m_y;
    QQuaternion q_y = QQuaternion::fromAxisAndAngle(0, 1, 0, rotation.x());
    m_y.rotate(q_y);
    imp_->world_y_rotation_matrix_ = imp_->world_y_rotation_matrix_ * m_y;

    QMatrix4x4 m_x;
    QMatrix4x4 camera_matrx = imp_->current_camera_->toMatrix().inverted();
    QVector3D axis = camera_matrx * QVector3D(1, 0, 0) - camera_matrx * QVector3D(0, 0, 0);
    QQuaternion q_x = QQuaternion::fromAxisAndAngle(axis, rotation.y());
    m_x.rotate(q_x);
    imp_->world_x_rotation_matrix_ = imp_->world_x_rotation_matrix_ * m_x;
}

void SceneRender::wheel(int delta)
{
    float factor = 1.0f - 0.1f*delta;

    float angle = imp_->current_camera_->verticalAngle()*factor;
    if(angle > MAX_PERSPECTIVE_ANGLE){
        angle = MAX_PERSPECTIVE_ANGLE;
    }

    if(angle < MIN_PERSPECTIVE_ANGLE){
        angle = MIN_PERSPECTIVE_ANGLE;
    }

    imp_->current_camera_->perspective(angle,
                                 imp_->current_camera_->aspectRatio(),
                                 imp_->current_camera_->nearPlane(),
                                 imp_->current_camera_->forPlane());
}

dream::Camera *SceneRender::currentCamera()
{
    return imp_->current_camera_;
}

void SceneRender::setCurrentCamera(dream::Camera *camera)
{
    if(camera != nullptr){
        imp_->current_camera_ = camera;
    }
    else{
        imp_->current_camera_ = imp_->default_world_camera_;
    }

}

void SceneRender::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    {
        glViewport(0, 0, imp_->viewport_.width(), imp_->viewport_.height());
        QMatrix4x4 m = imp_->world_scale_matrix_ *
                imp_->world_x_rotation_matrix_ *
                imp_->world_y_rotation_matrix_;

        if(imp_->current_camera_ != nullptr){
            QMatrix4x4 camera_matrx = imp_->current_camera_->toMatrix();
            m = imp_->world_tranlation_matrix_ * camera_matrx * m;
        }

        imp_->env_render_->updateWorldMatrix(m);
        imp_->geo_render_->updateWorldMatrix(m);

        imp_->env_render_->render();

        if(imp_->scene_ != nullptr){
            QList<dream::Geometry *> geo_list = imp_->scene_->findChildren<dream::Geometry*>();
            for(dream::Geometry *geo : geo_list){
                imp_->geo_render_->render(geo);
            }
        }
    }

    {
        glViewport(0, 0, 100, 100);

        QMatrix4x4 m =
                imp_->axis_matrix_ *
                imp_->world_x_rotation_matrix_ *
                imp_->world_y_rotation_matrix_;

        imp_->geo_render_->updateWorldMatrix(m);
        imp_->geo_render_->render(imp_->axis_);
        QList<dream::Geometry *> geo_list = imp_->axis_->findChildren<dream::Geometry*>();
        for(dream::Geometry *geo : geo_list){
            imp_->geo_render_->render(geo);
        }
    }
}

QMatrix4x4 SceneRender::rotationMatrix()
{
    return
        imp_->world_x_rotation_matrix_ *
            imp_->world_y_rotation_matrix_;
}

void SceneRender::setViewport(const QRect &view_port)
{
    imp_->viewport_ = view_port;

    imp_->current_camera_->perspective(imp_->current_camera_->verticalAngle(),
                                 static_cast<float>(imp_->viewport_.width())/imp_->viewport_.height(),
                                 imp_->current_camera_->nearPlane(),
                                 imp_->current_camera_->forPlane());
}
