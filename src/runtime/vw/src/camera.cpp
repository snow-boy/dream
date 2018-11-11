#include "camera.h"
#include <QtDebug>

namespace vw
{

class Camera::Imp
{
public:
    Imp():
        eye({0, 2, 0}),
        center({0, 0, 0}),
        up({1, 0, 0}),
        vertical_angle(160),
        aspect_ratio(1),
        near_plane(-1),
        far_plane(-2)
    {}

    QVector3D eye;
    QVector3D center;
    QVector3D up;

    float vertical_angle;
    float aspect_ratio;
    float near_plane;
    float far_plane;
};

Camera::Camera(QObject *parent):
    Entity (parent)
{
    imp_ = std::make_unique<Imp>();
    setRotation(QQuaternion::fromAxisAndAngle({0, 1, 0}, -45)*
                QQuaternion::fromAxisAndAngle({0, 0, 1}, -45));
}

Camera::~Camera()
{

}

void Camera::lookAt(const QVector3D &eye, const QVector3D &center, const QVector3D &up)
{
    imp_->eye = eye;
    imp_->center = center;
    imp_->up = up;
}

QVector3D Camera::eye() const
{
    return imp_->eye;
}

QVector3D Camera::center() const
{
    return imp_->center;
}

QVector3D Camera::up() const
{
    return imp_->up;
}

void Camera::perspective(float vertical_angle, float aspect_ratio, float near_plane, float far_plane)
{
    imp_->vertical_angle = vertical_angle;
    imp_->aspect_ratio = aspect_ratio;
    imp_->near_plane = near_plane;
    imp_->far_plane = far_plane;
}

float Camera::verticalAngle() const
{
    return imp_->vertical_angle;
}

float Camera::aspectRatio() const
{
    return imp_->aspect_ratio;
}

float Camera::nearPlane() const
{
    return imp_->near_plane;
}

float Camera::forPlane() const
{
    return imp_->far_plane;
}

QMatrix4x4 Camera::toMatrix() const
{
    QMatrix4x4 m;

    m.lookAt({0, 2, 0}, {0, 0, 0}, {1, 0, 0});
    m.frustum(-1, 1, -2, 2, -0.5, -3);

    qDebug() << m*QVector3D({0.1f, 0.2f, 0.3f});

//    m.rotate(rotation());
//    m.lookAt(imp_->eye, imp_->center, imp_->up);
//    m.perspective(imp_->vertical_angle, imp_->aspect_ratio, imp_->near_plane, imp_->far_plane);

    return m;
}

}