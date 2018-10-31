//#include "gl_widget.h"
//#include <GL/glut.h>
#include <QDebug>
#include "circle.h"
#include "line.h"
#include "ellipse.h"
#include "region.h"
#include "polygon.h"

#include "mainwindow.h"
#include <QApplication>

point p1,p2,translate_point,selected_point,ecenter,px,py,seed_point;
int win_height,win_width;
int fixed_x,fixed_y;
int gl_widget::x_at_press=0;
int gl_widget::y_at_press=0;
int gl_widget::x_at_release=0;
int gl_widget::y_at_release=0;
//extern int flag,single_left_mouse,
int single_left_mouse=0;
gl_widget::gl_widget(QWidget *parent):QOpenGLWidget (parent)
{
}

void gl_widget::axis(){
//    cout<<glutGet(GLUT_WINDOW_HEIGHT)<<" "<<glutGet(GLUT_WINDOW_WIDTH)<<endl;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(1, 1, 1,0.2);
    glBegin(GL_LINES);
    glVertex2i(0,gl_widget::height()/2);
    glVertex2i(0,-gl_widget::height()/2);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(gl_widget::width()/2,0);
    glVertex2i(-gl_widget::width()/2,0);
    glEnd();
    glDisable(GL_BLEND);
}

void gl_widget::refresh2d(){
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(-gl_widget::width()/2, gl_widget::width()/2, -gl_widget::height()/2,gl_widget::height()/2 , 0.0, 1.0);
}

void gl_widget::draw_points(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void gl_widget::initializeGL()
{
    glClearColor(0,0,0,1);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquation( GL_MAX );
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_COLOR_MATERIAL);

}

void gl_widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    refresh2d();

    switch (value[0]) {
    case 1:
        object::clear_screen();
        value[0]=value[1];
        break;
    case 211:
        if (mouse==1){
            line *line_object = new line(pixelSize,object_color,object_pattern);
            line_object->simple_dda(p1,p2);
            object::all_objects.push_back(line_object);
            object::temp_objects.clear();
            value[1]=211;
            mouse=0;
        }
        break;
     case 212:
        if (mouse==1){
            line *line_object = new line(pixelSize,object_color,object_pattern);
            line_object->symmetric_dda(p1,p2);
            object::all_objects.push_back(line_object);
            object::temp_objects.clear();
            value[1]=212;
            mouse=0;
        }
        break;
     case 213:
        if (mouse==1){
            line *line_object = new line(pixelSize,object_color,object_pattern);
            line_object->bresenham(p1,p2);
            object::all_objects.push_back(line_object);
            object::temp_objects.clear();
            value[1]=213;
            mouse=0;
        }
        break;
     case 214:
        if (mouse==1){
            line *line_object = new line(pixelSize,object_color,object_pattern);
            line_object -> mid_point(p1,p2);
            object::all_objects.push_back(line_object);
            object::temp_objects.clear();
            value[1]=214;
            mouse=0;
        }
        break;
     case 221:
        if (mouse==1){
//            cout<<"Printing Circle(Mid Point)"<<endl;
            circle *circle_object = new circle(pixelSize,object_color,object_pattern);
            circle_object -> midpoint_circle(p1,p2);
            object::all_objects.push_back(circle_object);
            object::temp_objects.clear();
            value[1]=221;
            mouse=0;
        }
        break;
    case 231:
       if (emouse==1){
//            cout<<"Printing Ellipse(Mid Point)"<<endl;
           Ellipse *ellipse_object = new Ellipse(pixelSize,object_color,object_pattern);
           ellipse_object -> draw_ellipse(ecenter,px,py);
           object::all_objects.push_back(ellipse_object);
           object::temp_objects.clear();
           value[1]=231;
           mouse=0;
       }
       break;
    case 241:
       if (mouse==1){
           Polygon *polygon_object = new Polygon(pixelSize,object_color,object_pattern);
           polygon_object->draw_polygon(p1,p2);
           if(start_flag==1){
               object::all_objects.push_back(polygon_object);
               start_flag=0;
               same_poly_flag=1;
           }
           else if(same_poly_flag==1){
               unsigned i;
               for(i=0; i<polygon_object->points.size() ; i++){
                   object::all_objects[object::all_objects.size()-1]->points.push_back(make_pair(polygon_object->points[i].first,polygon_object->points[i].second));
               }
           }
           object::temp_objects.clear();
           value[1]=241;
           mouse=0;
       }
       if(gl_widget::enter_key_flag==1){
           same_poly_flag=0;
           last_poly_flag=1;

           Polygon *polygon_object = new Polygon(pixelSize,object_color,object_pattern);
           polygon_object->draw_polygon(p1,p2);
           unsigned i;
           for(i=0; i<polygon_object->points.size() ; i++){
               object::all_objects[object::all_objects.size()-1]->points.push_back(make_pair(polygon_object->points[i].first,polygon_object->points[i].second));
           }
           start_flag=1;
           enter_key_flag=0;
//           same_poly_flag=0;
           last_poly_flag=0;
           value[1]=241;
           value[0]=value[1];
       }
       break;
    case 251:
        if(mouse==1){
            Polygon *polygon_object = new Polygon(pixelSize,object_color,object_pattern);
            polygon_object->special_polygon(p1,p2);
            object::all_objects.push_back(polygon_object);
            object::temp_objects.clear();
            value[1]=251;
            mouse=0;
        }
        break;
     case 240:
        if(mouse==1){
            clip_window_on=1;
            clip_points.clear();
            clip_points.push_back(p1);
            clip_points.push_back(p2);
            mouse=0;
            value[0]=value[1];
        }
        break;
     case 3:

        if(single_left_mouse==1&&ctrl_key_flag==1){
            object::multiple_select(selected_point);
        }
        if(single_left_mouse==1&&ctrl_key_flag==0){
            object::select_object(selected_point);
        }
        mouse=0;
        single_left_mouse=0;
        value[1]=3;
        break;

    case 46:
        if(mouse==1){
            object::draw();
            QApplication::setOverrideCursor(Qt::WaitCursor);
            object::all_objects[unsigned(object::index_selected)]->fill_color[0]=fill_color[0];
            object::all_objects[unsigned(object::index_selected)]->fill_color[1]=fill_color[1];
            object::all_objects[unsigned(object::index_selected)]->fill_color[2]=fill_color[2];
            object::all_objects[unsigned(object::index_selected)]->fill_color[3]=fill_color[3];
            object::boundary_4fill(seed_point.x,seed_point.y,fill_color,object::all_objects[unsigned(object::index_selected)]->color);
            mouse=0;
            QApplication::restoreOverrideCursor();
            QApplication::processEvents();
        }
        break;
    case 47:
        if(mouse==1){
            QApplication::setOverrideCursor(Qt::WaitCursor);
            GLubyte back_color[3]={0,0,0};
//            glReadPixels(seed_point.x,seed_point.y-1,1,1,GL_RGB,GL_UNSIGNED_BYTE,back_color);
            Region *region_object = new Region(fill_color);
            object::draw();
            region_object->flood_fill(seed_point.x,seed_point.y,fill_color,back_color);
            object::all_objects.push_back(region_object);
            object::temp_objects.clear();
            value[0]=47;
            mouse=0;
            QApplication::restoreOverrideCursor();
            QApplication::processEvents();
        }
        break;
    case 411:
        line::line_clipping();
        value[0]=0;
        break;

    case 99:
        value[0]=value[1];
        break;
    }

    clip_window();
    if(clip_window_on==1){
        line::line_clipping();
    }
    if(object::selected_object_num>-1){
        object::redraw();
    }
    object::draw();
    axis();

}

int flag=0;
int turn = 1;
void gl_widget::mousePressEvent(QMouseEvent *event)
{
    win_height=gl_widget::height();
    win_width=gl_widget::width();
    if(event->button()==Qt::LeftButton){
        seed_point.x=event->x();
        seed_point.y=event->y();
        mouse=0;
        emouse=0;
        p1.x=event->x()-gl_widget::width()/2;
        p1.y=gl_widget::height()/2-event->y();
        selected_point.x=event->x()-gl_widget::width()/2;
        selected_point.y=gl_widget::height()/2-event->y();
        fixed_x= event->x()-gl_widget::width()/2;
        fixed_y =gl_widget::height()/2-event->y();
        flag=1;
        single_left_mouse=1;
        if(value[0]==231){
            switch (turn) {
            case 1:
                ecenter.x = event->x()-gl_widget::width()/2;
                ecenter.y = gl_widget::height()/2-event->y();
                turn=2;
                break;
            case 2:
                px.x = event->x()-gl_widget::width()/2;
                px.y = gl_widget::height()/2-event->y();
                turn=3;
                break;
            case 3:
                py.x = event->x()-gl_widget::width()/2;
                py.y = gl_widget::height()/2-event->y();
                turn=1;
                emouse=1;
                break;

            }
        }
    }
    else if(event->button()==Qt::RightButton){
        mouse=0;
        qDebug()<<event->button()<<" "<<Qt::RightButton;
    }

}

void gl_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(flag==1){
        p2.x=event->x()-gl_widget::width()/2;
        p2.y=gl_widget::height()/2-event->y();
        mouse=1;
        flag=0;
        update();
    }
}

void gl_widget::clip_window()
{
    glColor3ub(255,255,255);
    if(clip_points.size()!=0){
    point min,max;
    min = clip_points[0];
    max = clip_points[1];
    glBegin(GL_LINES);
    glVertex2i(min.x,min.y);
    glVertex2i(min.x,max.y);

    glVertex2i(min.x,max.y);
    glVertex2i(max.x,max.y);

    glVertex2i(max.x,min.y);
    glVertex2i(max.x,max.y);

    glVertex2i(min.x,min.y);
    glVertex2i(max.x,min.y);
    glEnd();
    }
}




