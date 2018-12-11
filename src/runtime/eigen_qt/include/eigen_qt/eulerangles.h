#ifndef EULERANGLES_H
#define EULERANGLES_H

#include <Eigen/Dense>
#include <QQuaternion>
#include <QVector3D>
#include <array>

class EulerAngles
{
public:
    typedef std::array<int, 3> RotationOrder;

    EulerAngles(const RotationOrder &order = {0, 1, 2});

    void setAngles(const QVector3D &angle);

    QVector3D angles() const;

    RotationOrder rotationOrder() const;

    EulerAngles toEulerAngles(const RotationOrder &order);

    void fromEigenQ(const Eigen::Quaternionf &q);

    Eigen::Quaternionf toEigenQ();

    void fromQtQ(const QQuaternion &q);

    QQuaternion toQtQ();

    float &operator[] (int i)
    {
        return angles_[i];
    }

private:
    RotationOrder order_;
    QVector3D angles_;
};

#endif // EULERANGLES_H
