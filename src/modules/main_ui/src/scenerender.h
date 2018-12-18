#ifndef SCENERENDER_H
#define SCENERENDER_H

#include <QObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector3D>
#include <QVector2D>
#include <QRect>

#include <vw/camera.h>
#include <vw/entity.h>
#include <vw/axis.h>

#include "envrender.h"
#include "geometryrender.h"

class SceneRender :
        public QObject,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit SceneRender(QObject *parent = nullptr);

    void initialize();

    void setScene(dream::Entity *scene);

    void translate(const QVector2D &translation);

    void rotate(const QVector2D &rotation);

    void wheel(int delta);

    dream::Camera *currentCamera();

    void setCurrentCamera(dream::Camera *camera);

    void render();

    QMatrix4x4 rotationMatrix();

    void setViewport(const QRect &view_port);

private:
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

#endif // SCENERENDER_H
