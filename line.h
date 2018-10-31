#ifndef LINE_H
#define LINE_H

#include "object.h"

class line : public object
{
public:
    line(int weight,GLubyte rang[],int line_pattern[8]);
    void symmetric_dda(point p1,point p2);
    void simple_dda(point p1,point p2);
    void bresenham(point p1,point p2);
    void mid_point(point p1,point p2);
    void translate(point);
    void rotate(double angle,point pivot);
    void scale(scale_struct scale_value,point pivot);
    static bool liang_barsky(object *obj,vector <point>);
    static void line_clipping();
};

#endif // LINE_H
