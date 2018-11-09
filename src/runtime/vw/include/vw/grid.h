#ifndef GRID_H
#define GRID_H

#include "geometry.h"

namespace vw
{

class VW_DECL Grid: public Geometry
{
    Q_OBJECT
public:
    explicit Grid(QObject *parent = nullptr);
    ~Grid();

    void setWidth(float w, int div_count);
    float width() const;
    int widthDivCount() const;

    void setLength(float l, int div_count);
    float Length() const;
    int lengthDivCount() const;

private:
    void build();

    class Imp;
    std::unique_ptr<Imp> imp_;
};

} // namespace vw

#endif // GRID_H
