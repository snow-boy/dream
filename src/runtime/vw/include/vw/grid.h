#ifndef GRID_H
#define GRID_H

#include "geometry.h"

namespace dream
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

} // namespace dream

#endif // GRID_H
