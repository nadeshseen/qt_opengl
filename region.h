#ifndef REGION_H
#define REGION_H

#include "object.h"
class Region: public object
{
public:
    Region(GLubyte *rang);
    void flood_fill(GLint x,GLint y, GLubyte fill_color[], GLubyte back_color[]);
};

#endif // REGION_H
