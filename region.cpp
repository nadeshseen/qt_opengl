#include "region.h"
#include "mainwindow.h"

Region::Region(GLubyte *rang)
{
    this->color[0]=rang[0];
    this->color[1]=rang[1];
    this->color[2]=rang[2];
    this->color[3]=rang[3];
    this->object_num=objectNumber;
    this->object_name="Region";
    this->thickness=1;
    this->pattern[0]=1;
    this->pattern[1]=1;
    this->pattern[2]=1;
    this->pattern[3]=1;
    this->pattern[4]=1;
    this->pattern[5]=1;
    this->pattern[6]=1;
    this->pattern[7]=1;
    objectNumber++;
}
GLubyte current[3];
void Region::flood_fill(GLint x,GLint y, GLubyte fill_color[], GLubyte back_color[])
{
    glReadPixels(x,win_height-y-1,1,1,GL_RGB,GL_UNSIGNED_BYTE,current);
//    if(current[0]!=back_color[0]||current[1]!=back_color[1]||current[2]!=back_color[2])
//            return;
//    if(current[0]==fill_color[0]&&current[1]==fill_color[1]&&current[2]==fill_color[2])
//            return;
    if(current[0]==back_color[0]&&current[1]==back_color[1]&&current[2]==back_color[2]){
        this->points.push_back(make_pair(x-win_width/2,win_height/2-y));
        glColor3ubv(fill_color);
        glPointSize(1);
        glBegin(GL_POINTS);
            glVertex2i(x - win_width/2,win_height/2 - y);
        glEnd();
        glFlush();
        flood_fill(x+1,y,fill_color,back_color);
        flood_fill(x-1,y,fill_color,back_color);
        flood_fill(x,y+1,fill_color,back_color);
        flood_fill(x,y-1,fill_color,back_color);
    }
}
