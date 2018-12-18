#ifndef CONE_H
#define CONE_H

#include "geometry.h"

namespace dream
{

class VW_DECL Cone: public Geometry
{
    Q_OBJECT
public:
    explicit Cone(QObject *parent = nullptr);
    ~Cone();

    void setBottomR(float r);
    float bottomR() const;

    void setHeight(float height);
    float height() const;

    void setSegments(int segments);
    int segments() const;

private:
    void build();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace dream

#endif // CONE_H
