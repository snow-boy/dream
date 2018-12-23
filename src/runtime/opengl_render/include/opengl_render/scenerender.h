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

#include <memory>

#include "opengl_render_global.h"

class OPENGL_RENDER_DECL SceneRender :
        public QObject,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit SceneRender(QObject *parent = nullptr);
    ~SceneRender();

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
    class Imp;
    std::unique_ptr<Imp> imp_;
};

#endif // SCENERENDER_H
