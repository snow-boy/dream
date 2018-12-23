#ifndef ENVRENDER_H
#define ENVRENDER_H

#include <QObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <vw/grid.h>
#include "geometryrender.h"

class EnvRender :
        public QObject,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit EnvRender(QObject *parent = nullptr);

    void initialize();

    void updateWorldMatrix(const QMatrix4x4 &m)
    {
        world_matrix_ = m;
        geo_render_->updateWorldMatrix(m);
    }

    void render();

private:
    void makeObject();

    QMatrix4x4 world_matrix_;
    QOpenGLVertexArrayObject *vao_;
    QOpenGLBuffer *vbo_;
    QOpenGLShaderProgram *shader_program_;

    GeometryRender *geo_render_;
    dream::Grid *grid_;
};

#endif // ENVRENDER_H
