#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include <vw/entity.h>
#include <vw/geometry.h>
#include <vw/camera.h>

#include "envrender.h"
#include "geometryrender.h"

class SceneView :
        public QOpenGLWidget,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);
    ~SceneView();

    void setScene(vw::Entity *scene);
    void setCurrentCamera(vw::Camera *camer);

signals:

public slots:

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void wheelEvent(QWheelEvent *e) override;

    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    void renderScene();

    QMatrix4x4 world_y_rotation_matrix_;
    QMatrix4x4 world_x_rotation_matrix_;
    QMatrix4x4 world_tranlation_matrix_;
    QMatrix4x4 world_scale_matrix_;

    vw::Entity *scene_;

    QPoint last_pos_;

    EnvRender *env_render_;
    GeometryRender *geo_render_;
    vw::Camera *current_camera_;
};

#endif // SCENEVIEW_H
