#include "eulerangles.h"

#define _USE_MATH_DEFINES
#include <math.h>

EulerAngles::EulerAngles(const RotationOrder &order):
    order_(order),
    angles_({0, 0, 0})
{

}

void EulerAngles::setAngles(const QVector3D &angle)
{
    angles_ = angle;
}

QVector3D EulerAngles::angles() const
{
    return angles_;
}

EulerAngles::RotationOrder EulerAngles::rotationOrder() const
{
    return order_;
}

EulerAngles EulerAngles::toEulerAngles(const EulerAngles::RotationOrder &order)
{
    EulerAngles euler_angles(order);
    euler_angles.fromEigenQ(toEigenQ());
    return euler_angles;
}

void EulerAngles::fromEigenQ(const Eigen::Quaternionf &q)
{
    Eigen::Matrix3f m(q);
    Eigen::Vector3f angles = m.eulerAngles(order_[0], order_[1], order_[2]);
    for(int i = 0; i < 3; ++i){
        angles_[i] = angles[i]/M_PI*180.0f;
    }
}

Eigen::Quaternionf EulerAngles::toEigenQ()
{
    Eigen::Vector3f axis1(0, 0, 0);
    axis1[order_[0]] = 1;

    Eigen::Vector3f axis2(0, 0, 0);
    axis2[order_[1]] = 1;

    Eigen::Vector3f axis3(0, 0, 0);
    axis3[order_[2]] = 1;

    Eigen::Quaternionf q = Eigen::AngleAxisf(angles_[0]/180.0f*M_PI, axis1)
            *Eigen::AngleAxisf(angles_[1]/180.0f*M_PI, axis2)
            *Eigen::AngleAxisf(angles_[2]/180.0f*M_PI, axis3);

    return q;
}

void EulerAngles::fromQtQ(const QQuaternion &q)
{
    Eigen::Quaternionf eigen_q;
    eigen_q.x() = q.x();
    eigen_q.y() = q.y();
    eigen_q.z() = q.z();
    eigen_q.w() = q.scalar();
    fromEigenQ(eigen_q);
}

QQuaternion EulerAngles::toQtQ()
{
    Eigen::Quaternionf eigen_q = toEigenQ();
    QQuaternion q;
    q.setX(eigen_q.x());
    q.setY(eigen_q.y());
    q.setZ(eigen_q.z());

    return q;
}

