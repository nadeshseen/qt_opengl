#ifndef POLYGON_H
#define POLYGON_H
#include "object.h"

class Polygon : public object
{
public:


    Polygon(int weight,GLubyte *rang,int line_pattern[8]);
    void draw_polygon(point,point);
    void group();
    void special_polygon(point,point);
    void weiler_atherton(int);

};

#endif // POLYGON_H
