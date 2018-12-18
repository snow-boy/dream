#ifndef AXIS_H
#define AXIS_H

#include "geometry.h"

namespace dream
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
    void clear();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace dream

#endif // AXIS_H
