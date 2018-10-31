#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "object.h"

class Ellipse : public object
{
public:
    Ellipse(int weight,GLubyte *rang,int line_pattern[8]);
    void draw_ellipse(point center,point px,point py);
    void translate(point);
    void rotate(double angle, point pivot);
    void scale(scale_struct, point);
};

#endif // ELLIPSE_H
