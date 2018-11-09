#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

namespace vw
{

class VW_DECL Camera: public Entity
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();

    void lookAt(const QVector3D & eye, const QVector3D & center, const QVector3D & up);

    QVector3D eye() const;
    QVector3D center() const;
    QVector3D up() const;

    void perspective(float vertical_angle, float aspect_ratio, float near_plane, float far_plane);

    float verticalAngle() const;
    float aspectRatio() const;
    float nearPlane() const;
    float forPlane() const;

    QMatrix4x4 toMatrix() const;

private:
    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // CAMERA_H
