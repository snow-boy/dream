#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QOpenGLWidget>
#include <QMatrix4x4>

#include <vw/entity.h>
#include <vw/geometry.h>
#include <vw/camera.h>
#include <vw/axis.h>

#include <opengl_render/scenerender.h>

class SceneView :
        public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);
    ~SceneView();

    void setScene(dream::Entity *scene);
    void setCurrentCamera(dream::Camera *camer);

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
    QPoint last_pos_;

    SceneRender *scene_render_;
};

#endif // SCENEVIEW_H
