#ifndef ENVRENDER_H
#define ENVRENDER_H

#include <QObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class EnvRender :
        public QObject,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit EnvRender(QObject *parent = nullptr);

    void initialize();

    void setCurrentMatrix(const QMatrix4x4 &m)
    {
        current_m_ = m;
    }

    void render();

private:
    void makeObject();

    QMatrix4x4 current_m_;
    QOpenGLVertexArrayObject *vao_;
    QOpenGLBuffer *vbo_;
    QOpenGLShaderProgram *shader_program_;
};

#endif // ENVRENDER_H
