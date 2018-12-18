#include "envrender.h"

#include <vw/cube.h>

EnvRender::EnvRender(QObject *parent) :
    QObject(parent),
    vao_(nullptr),
    vbo_(nullptr),
    shader_program_(nullptr)
{
    geo_render_ = new GeometryRender(this);
    grid_ = new dream::Grid(this);
    grid_->setWidth(20, 20);
    grid_->setLength(20, 20);
    dream::Color *grid_color = new dream::Color(grid_);
    grid_color->setData(QColor(255, 255, 255, 20));
    grid_->addComponent(grid_color);
}

void EnvRender::initialize()
{
    initializeOpenGLFunctions();

    vao_ = new QOpenGLVertexArrayObject(this);
    vao_->create();
    Q_ASSERT(vao_->isCreated());
    vao_->bind();

    vbo_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo_->create();
    Q_ASSERT(vbo_->isCreated());
    vbo_->bind();
    makeObject();

    shader_program_ = new QOpenGLShaderProgram(this);
    shader_program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/env.vert");
    shader_program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/env.frag");
    bool ret = shader_program_->link();
    shader_program_->bind();
    Q_ASSERT(ret);

    shader_program_->setAttributeArray("position", nullptr, 3, 7*sizeof(float));
    shader_program_->enableAttributeArray("position");
    shader_program_->setAttributeArray("color", reinterpret_cast<float *>(3*sizeof(float)), 4, 7*sizeof(float));
    shader_program_->enableAttributeArray("color");

    vao_->release();

    geo_render_->initialize();
    render();
}

void EnvRender::makeObject()
{
    static GLfloat data[] =
    {
//        -1, 0, 0,
//        1, 0, 0, 0,

//        1, 0, 0,
//        1, 0, 0, 0,

//        0, 0, 1,
//        1, 0, 0, 0,

//        0, 0, -1,
//        1, 0, 0, 0,

//        1, 0, -1,
//        1, 1, 0, 0.5,

//        1, 0, 1,
//        1, 1, 0, 0.5,

//        -1, 0, 1,
//        1, 1, 0, 0.5,

//        -1, 0, -1,
//        1, 1, 0, 0.5,

        0, 0, 0,
        1, 0, 0, 1,

        1, 0, 0,
        1, 0, 0, 1,

        0, 0, 0,
        0, 1, 0, 1,

        0, 1, 0,
        0, 1, 0, 1,

        0, 0, 0,
        0, 0, 1, 1,

        0, 0, 1,
        0, 0, 1, 1
    };
    vbo_->allocate(data, sizeof(data));
}

void EnvRender::render()
{
    vao_->bind();
    world_matrix_.scale(0.5);
    shader_program_->setUniformValue("matrix", world_matrix_);

//    glLineWidth(5);
//    glDrawArrays(GL_LINES, 0, 6);

    vao_->release();

    geo_render_->render(grid_);
}

