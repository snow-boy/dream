#ifndef GEOMETRYRENDER_H
#define GEOMETRYRENDER_H

#include <QObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <vw/geometry.h>

class GeometryRender :
        public QObject,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit GeometryRender(QObject *parent = nullptr);

    void initialize();

    void updateWorldMatrix(const QMatrix4x4 &m)
    {
        world_matrix_ = m;
    }

    void render(dream::Geometry *geo);

private:
    QMatrix4x4 world_matrix_;

    QOpenGLVertexArrayObject *vao_;
    QOpenGLBuffer *vbo_;
    QOpenGLShaderProgram *shader_program_;
    QColor default_color_;
};

#endif // GEOMETRYRENDER_H
