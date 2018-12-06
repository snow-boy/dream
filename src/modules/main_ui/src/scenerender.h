#ifndef SCENERENDER_H
#define SCENERENDER_H

#include <QObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector3D>
#include <QVector2D>
#include <QRect>

#include <vw/camera.h>
#include <vw/entity.h>

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

    void setScene(vw::Entity *scene);

    void translate(const QVector2D &translation);

    void rotate(const QVector2D &rotation);

    void wheel(int delta);

    vw::Camera *currentCamera();

    void setCurrentCamera(vw::Camera *camera);

    void render();

private:
    vw::Entity *scene_;

    QMatrix4x4 world_y_rotation_matrix_;
    QMatrix4x4 world_x_rotation_matrix_;
    QMatrix4x4 world_tranlation_matrix_;
    QMatrix4x4 world_scale_matrix_;

    EnvRender *env_render_;
    GeometryRender *geo_render_;
    vw::Camera *current_camera_;
};

#endif // SCENERENDER_H
