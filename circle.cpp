#include "circle.h"
#define PI 3.14159265
circle::circle(int weight,GLubyte *rang,int line_pattern[8])
{
    this->thickness=weight;
    this->color[0]=rang[0];
    this->color[1]=rang[1];
    this->color[2]=rang[2];
    this->color[3]=rang[3];
    this->pattern[0]=line_pattern[0];
    this->pattern[1]=line_pattern[1];
    this->pattern[2]=line_pattern[2];
    this->pattern[3]=line_pattern[3];
    this->pattern[4]=line_pattern[4];
    this->pattern[5]=line_pattern[5];
    this->pattern[6]=line_pattern[6];
    this->pattern[7]=line_pattern[7];
    this->object_num=objectNumber;
    this->object_name="Circle";
    objectNumber++;
}

void circle::midpoint_circle(point p1, point p2)
{
    this->initial=p1;
    this->final=p2;

    GLint cx = p1.x;
    GLint x = p2.x;
    GLint cy = p1.y;
    GLint y = p2.y;
    vector<pair<int,int> > temp_points;
    GLint radius = pow((x-cx)*(x-cx)+(y-cy)*(y-cy),0.5);
    GLint ytemp,xtemp;
    ytemp= radius;
    xtemp = 0;
    GLfloat pk = 1-radius;
    while(ytemp>=xtemp){

        this->points.push_back(make_pair(int(xtemp)+cx,int(ytemp)+cy));
        temp_points.push_back(make_pair(int(xtemp),int(ytemp)));
        if(pk>=0){
            pk = pk+2*xtemp-2*ytemp+1;
            xtemp = xtemp+1;
            ytemp = ytemp-1;
        }
        else{
            pk = pk+2*xtemp+1;
            xtemp = xtemp+1;
        }
    }
    for( long i=points.size()-1;i>=0;i--){
        this->points.push_back(make_pair(int(temp_points[i].second)+cx,int(temp_points[i].first)+cy));
        temp_points.push_back(make_pair(int(temp_points[i].second),int(temp_points[i].first)));
    }
    for(long i=points.size()-1;i>=0;i--){
        this->points.push_back(make_pair(int(temp_points[i].first)+cx,-int(temp_points[i].second)+cy));
        temp_points.push_back(make_pair(int(temp_points[i].first),-int(temp_points[i].second)));
    }
    for(long i=points.size()-1;i>=0;i--){
        this->points.push_back(make_pair(-int(temp_points[i].first)+cx,int(temp_points[i].second)+cy));
        temp_points.push_back(make_pair(-int(temp_points[i].first),int(temp_points[i].second)));
    }
    this->algo_used="Midpoint";
}

void circle::translate(point t)
{
    Eigen::MatrixXd point_matrix(3,2);
    point_matrix(0,0)=object::transform_object->initial.x;
    point_matrix(1,0)=object::transform_object->initial.y;
    point_matrix(2,0)=1;
    point_matrix(0,1)=object::transform_object->final.x;
    point_matrix(1,1)=object::transform_object->final.y;
    point_matrix(2,1)=1;

    Eigen::MatrixXd translate_matrix(3,3);
    translate_matrix<<1,0,t.x,
                  0,1,t.y,
                  0,0,1;

    Eigen::MatrixXd new_points(3,2);
    new_points = translate_matrix*point_matrix;

    p1.x=int(new_points(0,0));
    p1.y=int(new_points(1,0));
    p2.x=int(new_points(0,1));
    p2.y=int(new_points(1,1));

    if(transform_object->algo_used=="Midpoint"){
        this->midpoint_circle(p1,p2);
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}
void circle::rotate(double angle, point pivot)
{
    Eigen::MatrixXd point_matrix(3,2);
    point_matrix(0,0)=object::transform_object->initial.x;
    point_matrix(1,0)=object::transform_object->initial.y;
    point_matrix(2,0)=1;
    point_matrix(0,1)=object::transform_object->final.x;
    point_matrix(1,1)=object::transform_object->final.y;
    point_matrix(2,1)=1;

    Eigen::MatrixXd rotate_matrix(3,3);
    rotate_matrix<<cos(angle*PI/180),-sin(angle*PI/180),0,
                  sin(angle*PI/180),cos(angle*PI/180),0,
                  0,0,1;
    Eigen::MatrixXd pos_matrix(3,3);
    pos_matrix<<1,0,pivot.x,
                  0,1,pivot.y,
                  0,0,1;
    Eigen::MatrixXd neg_matrix(3,3);
    neg_matrix<<1,0,-pivot.x,
                  0,1,-pivot.y,
                  0,0,1;
    Eigen::MatrixXd new_points(3,2);
    new_points = pos_matrix*rotate_matrix*neg_matrix*point_matrix;

    p1.x=int(new_points(0,0));
    p1.y=int(new_points(1,0));
    p2.x=int(new_points(0,1));
    p2.y=int(new_points(1,1));

    this->midpoint_circle(p1,p2);

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

void circle::scale(scale_struct S, point pivot)
{
    Eigen::MatrixXd point_matrix(3,2);
    point_matrix(0,0)=object::transform_object->initial.x;
    point_matrix(1,0)=object::transform_object->initial.y;
    point_matrix(2,0)=1;
    point_matrix(0,1)=object::transform_object->final.x;
    point_matrix(1,1)=object::transform_object->final.y;
    point_matrix(2,1)=1;

    Eigen::MatrixXd scale_matrix(3,3);
    scale_matrix<<S.x,0,0,
                  0,S.y,0,
                  0,0,1;
    Eigen::MatrixXd pos_matrix(3,3);
    pos_matrix<<1,0,pivot.x,
                  0,1,pivot.y,
                  0,0,1;
    Eigen::MatrixXd neg_matrix(3,3);
    neg_matrix<<1,0,-pivot.x,
                  0,1,-pivot.y,
                  0,0,1;
    Eigen::MatrixXd new_points(3,2);
    new_points = pos_matrix*scale_matrix*neg_matrix*point_matrix;

    p1.x=int(new_points(0,0));
    p1.y=int(new_points(1,0));
    p2.x=int(new_points(0,1));
    p2.y=int(new_points(1,1));

    this->midpoint_circle(p1,p2);

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}
