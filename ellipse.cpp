#include "ellipse.h"
#include<QDebug>
#define PI 3.14159265
Ellipse::Ellipse(int weight, GLubyte *rang, int line_pattern[])
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
    this->object_name="Ellipse";
    objectNumber++;
}

void Ellipse::draw_ellipse(point center, point px, point py)
{
    this->initial=center;
    this->final=px;
    this->final2=py;
    GLint cx = center.x;
    GLint cy = center.y;

    vector<pair<int,int> > temp_points;
    GLint rx = pow((px.x-cx)*(px.x-cx)+(px.y-cy)*(px.y-cy),0.5);
    GLint ry = pow((py.x-cx)*(py.x-cx)+(py.y-cy)*(py.y-cy),0.5);
    GLint ytemp,xtemp;
    ytemp= ry;
    xtemp = 0;
    GLfloat p1k = ry*ry-rx*rx*ry+rx*rx/4;

    while(2*xtemp*ry*ry<2*ytemp*rx*rx){
        this->points.push_back(make_pair(int(xtemp)+cx,int(ytemp)+cy));
        temp_points.push_back(make_pair(int(xtemp),int(ytemp)));
        if(p1k>=0){
            p1k = p1k+(2*xtemp+1)*ry*ry-2*ytemp*rx*rx;
            ytemp = ytemp-1;
        }
        else{
            p1k = p1k+(2*xtemp+1)*ry*ry;
        }
        xtemp = xtemp+1;
    }
    GLfloat p2k = ry*ry*(xtemp+0.5)*(xtemp+0.5)+rx*rx*(ytemp-1)*(ytemp-1)-rx*rx*ry*ry;
    while(2*xtemp*ry*ry>2*ytemp*rx*rx&&ytemp>=0){
        this->points.push_back(make_pair(int(xtemp)+cx,int(ytemp)+cy));
        temp_points.push_back(make_pair(int(xtemp),int(ytemp)));
        if(p2k>=0){
            p2k = p2k-(2*ytemp-1)*rx*rx;
        }
        else{
            p2k = p2k-(2*ytemp-1)*rx*rx+2*xtemp*ry*ry;
            xtemp = xtemp +1;
        }
        ytemp = ytemp-1;
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

void Ellipse::translate(point t)
{
    Eigen::MatrixXd point_matrix(3,3);
    point_matrix(0,0)=object::transform_object->initial.x;
    point_matrix(1,0)=object::transform_object->initial.y;
    point_matrix(2,0)=1;
    point_matrix(0,1)=object::transform_object->final.x;
    point_matrix(1,1)=object::transform_object->final.y;
    point_matrix(2,1)=1;
    point_matrix(0,2)=object::transform_object->final2.x;
    point_matrix(1,2)=object::transform_object->final2.y;
    point_matrix(2,2)=1;

    Eigen::MatrixXd translate_matrix(3,3);
    translate_matrix<<1,0,t.x,
                  0,1,t.y,
                  0,0,1;

    Eigen::MatrixXd new_points(3,3);
    new_points = translate_matrix*point_matrix;
    ecenter.x=int(new_points(0,0));
    ecenter.y=int(new_points(1,0));
    px.x=int(new_points(0,1));
    px.y=int(new_points(1,1));
    py.x=int(new_points(0,2));
    py.y=int(new_points(1,2));
    if(transform_object->algo_used=="Midpoint"){
        this->draw_ellipse(ecenter,px,py);
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

void Ellipse::rotate(double angle, point pivot)
{
    Eigen::MatrixXd point_matrix(3,object::transform_object->points.size());
    for(int i=0;i<object::transform_object->points.size();i++){
        point_matrix(0,i)=object::transform_object->points[i].first;
        point_matrix(1,i)=object::transform_object->points[i].second;
        point_matrix(2,i)=1;
    }
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
    Eigen::MatrixXd new_points(3,object::transform_object->points.size());
    new_points = pos_matrix*rotate_matrix*neg_matrix*point_matrix;

    for(int i=0;i<object::transform_object->points.size();i++){
        this->points.push_back(make_pair(new_points(0,i),new_points(1,i)));
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

void Ellipse::scale(scale_struct S, point pivot)
{
    Eigen::MatrixXd point_matrix(3,3);
    point_matrix(0,0)=object::transform_object->initial.x;
    point_matrix(1,0)=object::transform_object->initial.y;
    point_matrix(2,0)=1;
    point_matrix(0,1)=object::transform_object->final.x;
    point_matrix(1,1)=object::transform_object->final.y;
    point_matrix(2,1)=1;
    point_matrix(0,2)=object::transform_object->final2.x;
    point_matrix(1,2)=object::transform_object->final2.y;
    point_matrix(2,2)=1;

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
    Eigen::MatrixXd new_points(3,3);
    new_points = pos_matrix*scale_matrix*neg_matrix*point_matrix;
    ecenter.x=int(new_points(0,0));
    ecenter.y=int(new_points(1,0));
    px.x=int(new_points(0,1));
    px.y=int(new_points(1,1));
    py.x=int(new_points(0,2));
    py.y=int(new_points(1,2));
    this->draw_ellipse(ecenter,px,py);

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}
