#include "line.h"
#include <QDebug>
#include<iostream>
#define PI 3.14159265
line::line(int weight,GLubyte rang[],int line_pattern[8])
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
    this->object_num = objectNumber;
    this->object_name = "Line";
    objectNumber++;

}

void line::bresenham(point p1,point p2){
    this->initial=p1;
    this->final=p2;
    GLint x1 = p1.x;
    GLint x2 = p2.x;
    GLint y1 = p1.y;
    GLint y2 = p2.y;
    GLint deltax,deltay,maxValue,dx,dy;
    GLint xInc,yInc,xtemp,ytemp;
    dx=x2-x1;
    dy=y2-y1;
    deltax=abs(x2-x1);
    deltay=abs(y2-y1);
    if(abs(deltax)>abs(deltay)){
        maxValue = abs(deltax);
    }
    else{
        maxValue = abs(deltay);
    }

    int pk,pk1,i;
    xtemp=x1;
    ytemp=y1;
    if((deltay)<(deltax)){

        xInc=0;
        yInc=0;
        pk = 2*deltay - deltax;
        for(i=0;i<=maxValue;i++){
            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
            if(dx<0){
                xInc=-1;
            }
            else
                xInc=1;
            if(pk>=0){
                pk1=pk+2*deltay-2*deltax;
                pk=pk1;
            if(dy<0)
                yInc=-1;
            else
                yInc=1;
            }
            else{
                pk1=pk+2*deltay;
                pk=pk1;
                yInc=0;
            }
            xtemp = xtemp+xInc;
            ytemp = ytemp+yInc;
        }
    }
    else{
        xInc=0;
        yInc=0;
        pk = 2*deltax - deltay;
        for(i=0;i<=maxValue;i++){
            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
            if(dy<0)
                yInc=-1;
            else
                yInc=1;
            if(pk>=0){
                pk1=pk+2*deltax-2*deltay;
                pk=pk1;
                if(dx<0){
                    xInc=-1;
                }
                else
                    xInc=1;
            }
            else{
                pk1=pk+2*deltax;
                pk=pk1;
                xInc=0;
            }
            xtemp = xtemp+xInc;
            ytemp = ytemp+yInc;
        }
    }

    this->algo_used="Bresenham";
}
void line::mid_point(point p1,point p2){
    this->initial=p1;
    this->final=p2;
    GLint x1 = p1.x;
    GLint x2 = p2.x;
    GLint y1 = p1.y;
    GLint y2 = p2.y;
    GLint deltax,deltay,maxValue,dx,dy;
    GLint xInc,yInc,xtemp,ytemp;
    dx=x2-x1;
    dy=y2-y1;
    deltax=abs(x2-x1);
    deltay=abs(y2-y1);
    if(abs(deltax)>abs(deltay))
        maxValue = abs(deltax);
    else
        maxValue = abs(deltay);

    int pk,pk1,i;
    xtemp=x1;
    ytemp=y1;
    if(abs(deltay)<abs(deltax)){

        xInc=0;
        yInc=0;
        pk = 2*deltay - deltax;
        for(i=0;i<=maxValue;i++){
            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
            if(dx<0)
                xInc=-1;
            else
                xInc=1;
            if(pk>=0){
                pk1=pk+deltay-deltax;
                pk=pk1;
                if(dy<0)
                    yInc=-1;
                else
                    yInc=1;
            }
            else{
                pk1=pk+deltay;
                pk=pk1;
                yInc=0;
            }
            xtemp = xtemp+xInc;
            ytemp = ytemp+yInc;
        }
    }
    else{
        xInc=0;
        yInc=0;
        pk = 2*deltax - deltay;
        for(i=0;i<=maxValue;i++){
            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
            if(dy<0)
                yInc=-1;
            else
                yInc=1;
            if(pk>=0){
                pk1=pk+deltax-deltay;
                pk=pk1;
                if(dx<0)
                    xInc=-1;
                else
                    xInc=1;
            }
            else{
                pk1=pk+deltax;
                pk=pk1;
                xInc=0;
            }
            xtemp = xtemp+xInc;
            ytemp = ytemp+yInc;
        }
    }

    this->algo_used="Mid Point";
}
void line::simple_dda(point p1,point p2){
    this->initial=p1;
    this->final=p2;
    GLint x1 = p1.x;
    GLint x2 = p2.x;
    GLint y1 = p1.y;
    GLint y2 = p2.y;
    GLint deltax,deltay,lle;
    GLfloat xInc,yInc,xtemp,ytemp;
    deltax=x2-x1;
    deltay=y2-y1;
    if(abs(deltax)>abs(deltay)){
        lle = abs(deltax);
    }
    else{
        lle = abs(deltay);
    }
    xInc = deltax/float(lle);
    yInc = deltay/float(lle);
    xtemp = x1;
    ytemp = y1;
    int i;
    for(i=0;i<=lle;i++){
            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
        xtemp = xtemp+xInc;
        ytemp = ytemp+yInc;
    }
    this->algo_used="Simple DDA";

}
void line::symmetric_dda(point p1,point p2){
    this->initial=p1;
    this->final=p2;
    GLint x1 = p1.x;
    GLint x2 = p2.x;
    GLint y1 = p1.y;
    GLint y2 = p2.y;
    GLint deltax,deltay;
    GLfloat epsilon,lle, maxDiff;
    lle = 0;
    GLfloat xInc,yInc,xtemp,ytemp;
    deltax = x2-x1;
    deltay = y2-y1;
    epsilon =0;
    if(abs(deltax)>abs(deltay)){
        maxDiff = abs(deltax);
    }
    else{
        maxDiff = abs(deltay);
    }
    int i;
    for(i=1;i<=maxDiff;i++){
        if(maxDiff<float(pow(2,i)) && maxDiff>=float(pow(2,i-1))){
            lle = float(pow(2,i));
            epsilon = float(pow(2,-i));
            break;
        }
    }
    xInc = epsilon*deltax;
    yInc = epsilon*deltay;
    xtemp = x1;
    ytemp = y1;
    for(i=1;i<=lle;i++){
        this->points.push_back(make_pair(int(xtemp),int(ytemp)));
        xtemp = xtemp+xInc;
        ytemp = ytemp+yInc;
    }

    this->algo_used="Symmetric DDA";
}

void line::translate(point t)
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

    if(transform_object->algo_used=="Simple DDA"){
        this->simple_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Symmetric DDA"){
        this->symmetric_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Bresenham"){
        this->bresenham(p1,p2);
    }
    else if(transform_object->algo_used=="Mid Point"){
        this->mid_point(p1,p2);
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

void line::rotate(double angle, point pivot)
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

    if(transform_object->algo_used=="Simple DDA"){
        this->simple_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Symmetric DDA"){
        this->symmetric_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Bresenham"){
        this->bresenham(p1,p2);
    }
    else if(transform_object->algo_used=="Mid Point"){
        this->mid_point(p1,p2);
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

void line::scale(scale_struct S, point pivot)
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

    if(transform_object->algo_used=="Simple DDA"){
        this->simple_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Symmetric DDA"){
        this->symmetric_dda(p1,p2);
    }
    else if(transform_object->algo_used=="Bresenham"){
        this->bresenham(p1,p2);
    }
    else if(transform_object->algo_used=="Mid Point"){
        this->mid_point(p1,p2);
    }

    all_objects[unsigned(index_selected)]=this;
    objectNumber=all_objects[all_objects.size()-1]->object_num+1;

    this->object_num=unsigned(selected_object_num);
}

bool line::liang_barsky(object *obj,vector <point> clip_points)
{
    point wmin,wmax;
    if(clip_points[0].x < clip_points[1].x){
        wmin.x = clip_points[0].x;
        wmax.x = clip_points[1].x;
    }
    else{
        wmin.x = clip_points[1].x;
        wmax.x = clip_points[0].x;
    }
    if(clip_points[0].y < clip_points[1].y){
        wmin.y = clip_points[0].y;
        wmax.y = clip_points[1].y;
    }
    else{
        wmin.y = clip_points[1].y;
        wmax.y = clip_points[0].y;
    }
    int dx,dy;
    dx = obj->final.x - obj->initial.x;
    dy = obj->final.y - obj->initial.y;
    int P[4],Q[4];
    P[0] = -dx;
    P[1] = dx;
    P[2] = -dy;
    P[3] = dy;
    Q[0] = obj->initial.x - wmin.x;
    Q[1] = wmax.x - obj->initial.x;
    Q[2] = obj->initial.y - wmin.y;
    Q[3] = wmax.y - obj->initial.y;
    float temp;
    float u2=1,u1=0;
    for(int i = 0; i < 4 ; i++){
        if(P[i]!=0){
            temp = float(Q[i])/float(P[i]);
            if(P[i]<0){
                if(temp>u1)
                    u1 = temp;
            }
            else{
                if(temp<u2)
                    u2 = temp;
            }
        }
    }
    int u1_cond = int(ceil(u1));
    int u2_cond = int(floor(u2));

    if(u1_cond==0&&u2_cond==1){
//        qDebug()<<"Not clipped";
        return false;
    }

    float initial_dx=0,final_dx=0,initial_dy=0,final_dy=0;
    if(u1<u2){
        final_dx = u2*dx;
        final_dy = u2*dy;
        initial_dx = u1*dx;
        initial_dy = u1*dy;
        obj->final.x = (obj->initial.x) + int(final_dx);
        obj->final.y = (obj->initial.y) + int(final_dy);
        obj->initial.x = (obj->initial.x) +int(initial_dx);
        obj->initial.y = (obj->initial.y) + int(initial_dy);

    }
    else{
//        qDebug()<<"Fully Clipped";
        return true;
    }


    if(obj->algo_used=="Simple DDA"){
        line *line_obj = new line(obj->thickness,obj->color,obj->pattern);
        line_obj->simple_dda(obj->initial,obj->final);
        all_objects.push_back(line_obj);
    }
    else if(obj->algo_used=="Symmetric DDA"){
        line *line_obj = new line(obj->thickness,obj->color,obj->pattern);
        line_obj->symmetric_dda(obj->initial,obj->final);
        all_objects.push_back(line_obj);
    }
    else if(obj->algo_used=="Bresenham"){
        line *line_obj = new line(obj->thickness,obj->color,obj->pattern);
        line_obj->bresenham(obj->initial,obj->final);
        all_objects.push_back(line_obj);
    }
    else if(obj->algo_used=="Mid Point"){
        line *line_obj = new line(obj->thickness,obj->color,obj->pattern);
        line_obj->mid_point(obj->initial,obj->final);
        all_objects.push_back(line_obj);
    }
    return true;
}

void line::line_clipping()
{
    unsigned long i;
    unsigned long obj_size = object::all_objects.size();
    for(i=0;i<obj_size;i++){
        if(object::all_objects[i]->object_name=="Line"){
            if(line::liang_barsky(object::all_objects[i],gl_widget::clip_points)==true){
                all_objects[i]->points.clear();
            }
        }
    }
    qDebug()<<"Erased ";
    for(unsigned i=0;i<all_objects.size();i++){
        if(object::all_objects[i]->object_name=="Line"){
            if(all_objects[i]->points.size()==0){
                all_objects.erase(all_objects.begin()+i);
                i=i-1;
            }
        }
    }

}
