#include "geometryrender.h"

GeometryRender::GeometryRender(QObject *parent) :
    QObject(parent),
    vao_(nullptr),
    vbo_(nullptr),
    shader_program_(nullptr),
    default_color_(141, 141, 146)
{

}

void GeometryRender::initialize()
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
}

void GeometryRender::render(vw::Geometry *geo)
{
    vao_->bind();
    vbo_->bind();

    QMatrix4x4 self_m;
    self_m.rotate(geo->rotation());
    self_m.translate(geo->position());
    self_m.scale(geo->scale());

    shader_program_->setUniformValue("matrix", world_matrix_ * self_m);
    glLineWidth(1.0f);

    QColor geo_color = default_color_;
    vw::Color *geo_color_component = geo->findComponent<vw::Color *>();
    if(geo_color_component != nullptr){
        geo_color = geo_color_component->data();
    }

    QVector<vw::Primitive *> primitive_list = geo->primitives();
    for(vw::Primitive *primitive : primitive_list){
        QColor primitive_color = geo_color;
        vw::Color *primitive_color_component = primitive->findComponent<vw::Color *>();
        if(primitive_color_component != nullptr){
            primitive_color = primitive_color_component->data();
        }

        QVector<GLfloat> data;
        QVector<vw::Vertex *> vertex_list = primitive->vertexList();
        for(vw::Vertex *vertex : vertex_list){
            QVector3D vertex_data = vertex->data();
            data.append(vertex_data.x());
            data.append(vertex_data.y());
            data.append(vertex_data.z());

            QColor vertex_color = primitive_color;
            vw::Color *vertex_color_component = vertex->findComponent<vw::Color *>();
            if(vertex_color_component != nullptr){
                vertex_color = vertex_color_component->data();
            }

            data.append(vertex_color.redF());
            data.append(vertex_color.greenF());
            data.append(vertex_color.blueF());
            data.append(vertex_color.alphaF());
        }

        static QMap<vw::Primitive::PrimitiveType, GLenum> primitive_map =
        {
            {vw::Primitive::LINES, GL_LINES},
            {vw::Primitive::LINE_LOOP, GL_LINE_LOOP},
            {vw::Primitive::LINE_STRIP, GL_LINE_STRIP},
            {vw::Primitive::POINTS, GL_POINTS},
            {vw::Primitive::POLYGON, GL_POLYGON},
            {vw::Primitive::QUADS, GL_QUADS},
            {vw::Primitive::QUAD_STRIP, GL_QUAD_STRIP},
            {vw::Primitive::TRIANGLES, GL_TRIANGLES},
            {vw::Primitive::TRIANGLE_FAN, GL_TRIANGLE_FAN},
            {vw::Primitive::TRIANGLE_STRIP, GL_TRIANGLE_STRIP},
        };

        vbo_->allocate(data.data(), data.size()*sizeof(float));
        glDrawArrays(primitive_map[primitive->primitiveType()], 0, data.size()/7);
    }

    vao_->release();
}
