#ifndef AXIS_H
#define AXIS_H

#include "geometry.h"

namespace vw
{

class VW_DECL Axis : public Geometry
{
    Q_OBJECT
public:
    explicit Axis(QObject *parent = nullptr);
    ~Axis();

    void hideArray();
    void showArray();

    void setArrowBottomR(float r);
    float arrowBottomR();

    void setArrowLength(float length);
    float arrowLength();

    void setArrowSegments(int segments);
    int arrowSegments();

    void setLength(float len);
    float length();

private:
    void build();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // AXIS_H
