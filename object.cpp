//#include "object.h"
#include "mainwindow.h"
//#include<iostream>
#include"math.h"
//#include<QDebug>
#define PI 3.14159265
object::object()
{

}


void object::draw(){
    unsigned long j,i,l;
    int k=0;
    int *object_patt;
    for(i=0;i<all_objects.size();i++){
        for(j=0;j<all_objects[i]->points.size();j++){
            glPointSize(all_objects[i]->thickness);
            glColor4ub(all_objects[i]->color[0],all_objects[i]->color[1],all_objects[i]->color[2],all_objects[i]->color[3]);
            object_patt = all_objects[i]->pattern;
            if(k==8)
                k=0;
            if(object_patt[k]==1)
                gl_widget::draw_points(int(all_objects[i]->points[j].first),int(all_objects[i]-> points[j].second));
            k++;
        }
    }

    for(i=0;i<all_objects.size();i++)
        for(l=0;l<all_objects[i]->filled_points.size();l++){
            glPointSize(1);
            glColor4ub(all_objects[i]->fill_color[0],all_objects[i]->fill_color[1],all_objects[i]->fill_color[2],1);
            gl_widget::draw_points(int(all_objects[i]->filled_points[l].first),int(all_objects[i]->filled_points[l].second));
        }

}

void object::clear_screen()
{
    all_objects.clear();
    all_objects.shrink_to_fit();
}

void object::redraw(){
    unsigned long j,i,k;
    for(i=0;i<list_obj_index.size();i++){
                k=unsigned(list_obj_index[i]);
                for(j=0;j<all_objects[k]->points.size();j++){
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                    glColor4d(1, 0.0431373, 0.0431373,0.15);
                    glPointSize(all_objects[k]->thickness+5);
                    gl_widget::draw_points(int(all_objects[k]->points[j].first), int(all_objects[k]->points[j].second));
                    glDisable(GL_BLEND);
            }
    }
}
void object::select_object(point p)
{
    unsigned long j,i;
    int flag=0;
    object::index_selected=-1;
    object::selected_object_num=-1;
    for(i=0;i<all_objects.size();i++)
        for(j=0;j<all_objects[i]->points.size();j++){
            if((all_objects[i]->points[j].first+4 >= p.x && all_objects[i]->points[j].first-4 <= p.x) && (all_objects[i]-> points[j].second+4 >= p.y && all_objects[i]->points[j].second-4 <= p.y)){
                object::index_selected=int(i);
                object::selected_object_num=int(all_objects[i]->object_num);
                list_obj_index.clear();
                list_obj_index.push_back(index_selected);
                list_obj_num.clear();
                list_obj_num.push_back(selected_object_num);
//                redraw();
                flag=1;
            }
            if(flag==1)
                break;
        }
}

void object::multiple_select(point p)
{
    unsigned long j,i;
    int flag=0;
    object::index_selected=-1;
    object::selected_object_num=-1;
    for(i=0;i<all_objects.size();i++)
        for(j=0;j<all_objects[i]->points.size();j++){
            if((all_objects[i]->points[j].first+4 >= p.x && all_objects[i]->points[j].first-4 <= p.x) && (all_objects[i]-> points[j].second+4 >= p.y && all_objects[i]->points[j].second-4 <= p.y)){
                object::index_selected=int(i);
                object::selected_object_num=int(all_objects[i]->object_num);
                list_obj_index.push_back(index_selected);
                list_obj_num.push_back(selected_object_num);
                flag=1;
            }
            if(flag==1){
                break;
            }
        }
    unsigned k;
    int pop_flag=0;
    for(k = 0; k < list_obj_num.size()-1; k++){
        if(list_obj_num[k]==selected_object_num){
            list_obj_index.erase(list_obj_index.begin()+k);
            list_obj_num.erase(list_obj_num.begin()+k);
            pop_flag=1;
            k=k-1;
        }
    }
    if(pop_flag==1){
        list_obj_index.pop_back();
        list_obj_num.pop_back();
    }
//    qDebug()<<list_obj_index.size()<<list_obj_index.size();
//    redraw();
}

int object::undo()
{
    if(all_objects.empty()){
        return 0;
    }
    temp_objects.push_back(all_objects[all_objects.size()-1]);
    all_objects.pop_back();
    all_objects.shrink_to_fit();
    object::objectNumber--;
    return 0;
}

int object::redo()
{
    if(temp_objects.empty()){
        return 0;
    }
    all_objects.push_back(temp_objects.back());
    temp_objects.pop_back();
    object::objectNumber++;
    return 0;
}

void object::delete_object()
{
//    unsigned int selected = unsigned(selected_object);
    //    selected= unsigned(selected);
    unsigned int i,j;
    for(j=0;j<list_obj_index.size();j++){
        unsigned long selected=unsigned(list_obj_num[j]);
        for(i=0;i<all_objects.size();i++){
            if(all_objects[i]->object_num==selected){
                temp_objects.push_back(all_objects[i]);
                all_objects.erase(all_objects.begin()+i);
                object::selected_object_num=-1;
                break;
            }
        }
    }
}


void object::set_pattern(int line_pattern[])
{
//    if(object::selected_object_num>-1){
    unsigned long i;
    for(i=0;i<list_obj_index.size();i++){
        unsigned long object_index=unsigned(list_obj_index[i]);
        object::all_objects[object_index]->pattern[0]=line_pattern[0];
        object::all_objects[object_index]->pattern[1]=line_pattern[1];
        object::all_objects[object_index]->pattern[2]=line_pattern[2];
        object::all_objects[object_index]->pattern[3]=line_pattern[3];
        object::all_objects[object_index]->pattern[4]=line_pattern[4];
        object::all_objects[object_index]->pattern[5]=line_pattern[5];
        object::all_objects[object_index]->pattern[6]=line_pattern[6];
        object::all_objects[object_index]->pattern[7]=line_pattern[7];

    }
    value[0]=value[1];
//    }
}

void object::set_color(GLubyte rang[])
{
    unsigned long i;
    for(i=0;i<list_obj_index.size();i++){
        unsigned long object_index=unsigned(list_obj_index[i]);
        object::all_objects[object_index]->color[0]=rang[0];
        object::all_objects[object_index]->color[1]=rang[1];
        object::all_objects[object_index]->color[2]=rang[2];
        object::all_objects[object_index]->color[3]=rang[3];
    }
//    value[0]=value[1];
}

void object::set_thickness(int weight)
{
    unsigned long i;
    for(i=0;i<list_obj_index.size();i++){
        unsigned long object_index=unsigned(list_obj_index[i]);
        object::all_objects[object_index]->thickness=weight;
    }
    value[0]=value[1];
}



void object::boundary_4fill(GLint x,GLint y, GLubyte fill[], GLubyte bc[])
{
    GLubyte current[3];
    glReadPixels(x,win_height-y-1,1,1,GL_RGB,GL_UNSIGNED_BYTE,current);
    if((current[0]!=bc[0]||current[1]!=bc[1]||current[2]!=bc[2])&&
            (current[0]!=fill[0]||current[1]!=fill[1]||current[2]!=fill[2])){
        all_objects[unsigned(index_selected)]->filled_points.push_back(make_pair(x-win_width/2,win_height/2-y));

        glColor3ubv(fill);
        glPointSize(1);
        glBegin(GL_POINTS);
        glVertex2i(x - win_width/2,win_height/2 - y);
        glEnd();
        glFlush();
        boundary_4fill(x+1,y,fill,bc);
        boundary_4fill(x-1,y,fill,bc);
        boundary_4fill(x,y+1,fill,bc);
        boundary_4fill(x,y-1,fill,bc);

    }
}


