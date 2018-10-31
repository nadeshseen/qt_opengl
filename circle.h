#ifndef CIRCLE_H
#define CIRCLE_H
#include "object.h"

class circle : public object
{
public:
    circle(int weight,GLubyte *rang,int line_pattern[8]);
    void midpoint_circle(point p1,point p2);
    void translate(point);
    void rotate(double angle, point pivot);
    void scale(scale_struct, point);
};

#endif // CIRCLE_H
