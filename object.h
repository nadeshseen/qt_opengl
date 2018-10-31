#ifndef OBJECT_H
#define OBJECT_H
#include <math.h>
#include "gl_widget.h"
#include<eigen3/Eigen/Dense>
#include<QString>
using namespace std;


struct scale_struct{
    double x,y;
};

class object
{
public:
    GLubyte color[4];
    GLubyte fill_color[4];
    int pattern[8];
    GLint thickness;
    unsigned int object_num;
    QString object_name;
    QString algo_used;
    point initial,final,final2;
    static inline unsigned int objectNumber=0;
    vector<pair<int,int> > points;
    vector<pair<int,int> > filled_points;
    static inline vector <object*> all_objects;
    static inline object* transform_object;
    static inline object* temp_transform;
    static inline GLubyte back_color[4]={0,0,0,1};
    static inline vector<object*> temp_objects;
    static inline int index_selected=-1;
    static inline int selected_object_num= -1;
    static inline int scale_x=1,scale_y=1;
    static inline vector<int> list_obj_num;
    static inline vector<int> list_obj_index;
    vector <pair<point,point>> end_points;
    object();

    static void draw();
    static void redraw();
    static void clear_screen();
    static void select_object(point p);
    static void multiple_select(point p);
    static int undo();
    static int redo();
    static void delete_object();
    static void set_pattern(int line_pattern[]);
    static void set_color(GLubyte rang[]);
    static void set_thickness(int weight);
    static void boundary_4fill(GLint, GLint , GLubyte fill[], GLubyte bc[] );

};


#endif // OBJECT_H
