#include "polygon.h"

#include <QDebug>
#define PI 3.14159265
Polygon::Polygon(int weight, GLubyte *rang, int line_pattern[])
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
    this->object_name="Polygon";
    objectNumber++;
}

struct triplet{
    point coordinate;
    int name;
    int entry_flag;
};

void Polygon::weiler_atherton(int flag)
{
    object *clip_window = all_objects[unsigned(list_obj_index[1])];
    object *clipping_poly =all_objects[unsigned(list_obj_index[0])];
    unsigned j,k,l;
    vector <pair<point, int>> sub_list;
    vector <pair<point, int>> window_list;
    vector <triplet> intersection;
//    point p;
//    int x =0;
//    int y=0;
    int enter_flag = 1;
//    intersection.push_back({p,x,y});
    j=0;
    int small = 97;
    int capital = 65;
    int common = 0;
//    int found_flag=0;
//    vector <pair<point,int> > intersections;
//    vector <pair<point,int> > win_intersections;
//    for (unsigned i = 0 ; i<clip_window->end_points.size() ; i++ ){
//        for (unsigned j = 0 ; j<clipping_poly->end_points.size() ; j++ ){
////            point
//    }
    int min_x=clip_window->end_points[0].first.x,max_x=clip_window->points[0].first;
    for(l = 0 ; l<clip_window->points.size(); l++){
//        if(min_x>clip_window->points[l].first){
//            min_x = clip_window->points[l].first;
//        }
        if(max_x<clip_window->points[l].first){
            max_x = clip_window->points[l].first;
        }
    }
    for(l=0 ; l < clipping_poly->points.size(); l++){
//        if(min_x>clipping_poly->points[l].first){
//            min_x = clipping_poly->points[l].first;
//        }
        if(max_x<clipping_poly->points[l].first){
            max_x = clipping_poly->points[l].first;
        }
    }
    vector <pair<int,int> > ray_tracing;
    for(int i = min_x;i<max_x+5;i++){
//        this->points.push_back(make_pair(min_x,clipping_poly->points[0].second));
        ray_tracing.push_back(make_pair(min_x,clipping_poly->points[0].second));
        min_x++;
    }
    int inside = 0;
    for(unsigned i = 0 ; i<ray_tracing.size();i++){
        for(unsigned k=0;k<clip_window->points.size();k++){
            if(ray_tracing[i].first==clip_window->points[k].first && ray_tracing[i].second==clip_window->points[k].second){
//                qDebug()<<i<<" "<<k;
                inside = 1 - inside;
                i=i+4;
                break;

            }
        }
    }
//    qDebug()<<inside;
    if(inside==1){
        enter_flag=0;
    }
    window_list.push_back(make_pair(clip_window->end_points[0].first,capital));
    capital++;
    sub_list.push_back(make_pair(clipping_poly->end_points[0].first,small));
    small++;
    unsigned side_count_sub = 1;
    unsigned side_count_window = 1;
//    for(unsigned i = 0 ; i < clip_window->end_points.size() ; i++){
//        qDebug()<<clip_window->end_points[i].first.x<<" "<<clip_window->end_points[i].first.y;
//    }
//    for(k = 0 ; k<clip_window->points.size(); k++){
//        for(l=0 ; l < clipping_poly->points.size(); l++){
//            if(clip_window->points[k].first == clipping_poly->points[l].first && clip_window->points[k].second == clipping_poly->points[l].second){
//                point p;
//                p.x = clip_window->points[k].first;
//                p.y = clip_window->points[k].second;
//                intersection.push_back({p,common,enter_flag});
//                enter_flag = 1-enter_flag;
//                common++;
//                k+=2;
//                break;

//            }
//        }
//    }
//    common = 0;
    for(k = 0 ; k<clip_window->points.size(); k++){
        for(l=0 ; l < clipping_poly->points.size(); l++){
            if(clip_window->points[k].first == clipping_poly->points[l].first && clip_window->points[k].second == clipping_poly->points[l].second){
                point p;
                p.x = clip_window->points[k].first;
                p.y = clip_window->points[k].second;
                window_list.push_back(make_pair(p,common));
                common++;
                k=k+2;
                break;
            }
        }

        if(clip_window->end_points[side_count_window].first.x==clip_window->points[k].first && clip_window->end_points[side_count_window].first.y == clip_window->points[k].second){
            window_list.push_back(make_pair(clip_window->end_points[side_count_window].first,capital));
            capital++;
            side_count_window++;
        }
    }
    for(k = 0 ; k<clipping_poly->points.size(); k++){
        for(l=0 ; l < clip_window->points.size(); l++){
            if(clipping_poly->points[k].first == clip_window->points[l].first && clipping_poly->points[k].second == clip_window->points[l].second){
                point p;
                p.x = clipping_poly->points[k].first;
                p.y = clipping_poly->points[k].second;
                for(unsigned j = 0 ; j<window_list.size(); j++){
                    if(p.x == window_list[j].first.x &&p.y == window_list[j].first.y){
                        common = window_list[j].second;
                        break;
                    }
                }
                intersection.push_back({p,common,enter_flag});
                enter_flag=1-enter_flag;
                sub_list.push_back(make_pair(p,common));

                k=k+2;
                break;
            }
        }

        if(clipping_poly->end_points[side_count_sub].first.x==clipping_poly->points[k].first && clipping_poly->end_points[side_count_sub].first.y == clipping_poly->points[k].second){
            sub_list.push_back(make_pair(clipping_poly->end_points[side_count_sub].first,small));
            small++;
            side_count_sub++;
        }
    }
    int temp1 = -1;
    int temp2 = -1;
    unsigned index = 0;
    vector <pair<point,int> > poly_list;
    vector <vector<pair<point,int> > > list;

//    qDebug()<<"Sub List";

//    for(unsigned i = 0;i<sub_list.size(); i++){
//            qDebug()<<sub_list[i].second<<" ";
//        }

//    qDebug()<<"Window List";
//    for(unsigned i = 0;i<window_list.size(); i++){
//            qDebug()<<window_list[i].second<<" ";
//        }
//    index++;
//    temp1 = sub_list[index].second;
//    unsigned index_list = 0;
    int e_flag=1;
    if(flag==1){

//        for(unsigned l=0 ; l<li)
        while (e_flag==1){
            e_flag=0;
            for(unsigned i=0; i<intersection.size();i++){
                if(intersection[i].name<60 && intersection[i].entry_flag == 1){
                    temp2 = intersection[i].name;
                    break;
                }
            }
            for(unsigned i=0; i<sub_list.size();i++){
                if(sub_list[i].second == temp2){
                    index = i;
                    break;
                }
            }
            temp1=temp2;
            int sub_flag=1;
            do{
                if(sub_flag==0){
                    for(unsigned i = 0;i<window_list.size();i++){
                        if(temp1 == window_list[i].second){
                            index = i ;
                            break;
                        }
                    }

                    poly_list.push_back(window_list[index]);
                    index++;
                    if(index==window_list.size())
                        index=0;
                    temp1 = window_list[index].second;
                    if(temp1<60){
                        sub_flag=1;
                    }
                }
                else{
                    for(unsigned i = 0;i<sub_list.size();i++){
                        if(temp1 == sub_list[i].second){
                            index = i ;
                            break;
                        }
                    }

                    poly_list.push_back(sub_list[index]);
                    index++;
                    if(index==sub_list.size())
                        index=0;
                    temp1 = sub_list[index].second;
                    if(temp1<60){
                        sub_flag=0;
                    }
                }
            }while(temp2!=temp1);
            point p;
            p.x=0;
            p.y=0;
            poly_list.push_back(make_pair(p,-1));
            list.push_back(poly_list);
            //        qDebug()<<list[index_list].size()<<" "<<poly_list.size();
            for(unsigned k = 0 ; k < poly_list.size() ; k++){
                for(unsigned j = 0;j<intersection.size();j++){
                    if(poly_list[k].first.x==intersection[j].coordinate.x && poly_list[k].first.y == intersection[j].coordinate.y && poly_list[k].second == intersection[j].name){
                        intersection.erase(intersection.begin()+j);
                        break;
                    }
                }
            }
            for(unsigned k =0;k<intersection.size();k++){
                if(intersection[k].entry_flag==1){
                    e_flag=1;
                    break;
                }
            }
//            poly_list.clear();

        }


    }
    else if(flag==2){
        for(unsigned i=0; i<sub_list.size();i++){
            if(sub_list[i].second >60){
                temp2 = sub_list[0].second;
                index = i;
                break;
            }
        }
//        temp2 = sub_list[0].second;
        int sub_flag=1;
        temp1= temp2;

        do{
            if(sub_flag==0){
                for(unsigned i = 0;i<window_list.size();i++){
                    if(temp1 == window_list[i].second){
                        index = i ;
                        break;
                    }
                }

                poly_list.push_back(window_list[index]);
                index++;
                if(index==window_list.size())
                    index=0;
                temp1 = window_list[index].second;
                if(temp1<60){
                    sub_flag=1;
                }
            }
            else{
                for(unsigned i = 0;i<sub_list.size();i++){
                    if(temp1 == sub_list[i].second){
                        index = i ;
                        break;
                    }
                }

                poly_list.push_back(sub_list[index]);
                index++;
                if(index==sub_list.size())
                    index=0;
                temp1 = sub_list[index].second;
                if(temp1<60){
                    sub_flag=0;
                }
            }
        }while(temp2!=temp1);

        point p;
        p.x=0;
        p.y=0;
        poly_list.push_back(make_pair(p,-1));


    }
    else if(flag==3){
        int index=0;
        while(e_flag==1){
            e_flag=0;
            for(unsigned i=0; i<intersection.size();i++){
                if(intersection[i].entry_flag == 1){
                    temp2 = intersection[i].name;
                    break;
                }
            }
            for(unsigned i=0; i<window_list.size();i++){
                if(window_list[i].second == temp2){
                    index = int(i);
                    break;
                }
            }
            temp1=temp2;
            int sub_flag=0;
            //        temp2 = sub_list[0].second;
            //        int sub_flag=1;
            //        temp1= temp2;

            do{
                if(sub_flag==0){
                    for(unsigned i = 0;i<window_list.size();i++){
                        if(temp1 == window_list[i].second){
                            index = int(i) ;
                            break;
                        }
                    }

                    poly_list.push_back(window_list[unsigned(index)]);
                    index--;
                    if(index==-1)
                        index=int(window_list.size()-1);
                    temp1 = window_list[unsigned(index)].second;
                    if(temp1<60){
                        sub_flag=1;
                    }
                }
                else{
                    for(unsigned i = 0;i<sub_list.size();i++){
                        if(temp1 == sub_list[i].second){
                            index = int(i) ;
                            break;
                        }
                    }

                    poly_list.push_back(sub_list[unsigned(index)]);
                    index++;
                    if(index==int(sub_list.size()))
                        index=0;
                    temp1 = sub_list[unsigned(index)].second;
                    if(temp1<60){
                        sub_flag=0;
                    }
                }
            }while(temp2!=temp1);
            point p;
            p.x=0;
            p.y=0;
            poly_list.push_back(make_pair(p,-1));
            for(unsigned k = 0 ; k < poly_list.size() ; k++){
                for(unsigned j = 0;j<intersection.size();j++){
                    if( poly_list[k].second == intersection[j].name){
                        intersection.erase(intersection.begin()+j);
                        break;
                    }
                }
            }
            for(unsigned k =0;k<intersection.size();k++){
                if(intersection[k].entry_flag==1){
                    e_flag=1;
//                    qDebug()<<intersection[k].name;
                    break;
                }
            }
//            qDebug()<<"Nadesh";
        }
    }
//    list_obj_index.pop_back();
//    list_obj_num.pop_back();
    delete_object();
    unsigned count = 0;
    for(unsigned m = 0;m<poly_list.size()-1; m++){
        GLint x1,x2,y1,y2;

        if(poly_list[m].second==-1){
            m=m+1;
             x1 = poly_list[m].first.x;
             x2 = poly_list[m+1].first.x;
             y1 = poly_list[m].first.y;
             y2 = poly_list[m+1].first.y;
             count=0;
        }else if(poly_list[m+1].second==-1){
            x1 = poly_list[m].first.x;
            x2 = poly_list[m-count].first.x;
            y1 = poly_list[m].first.y;
            y2 = poly_list[m-count].first.y;
            count=0;
       }else{
            x1 = poly_list[m].first.x;
            x2 = poly_list[m+1].first.x;
            y1 = poly_list[m].first.y;
            y2 = poly_list[m+1].first.y;
        }
//        if(m-count!=0){
//            m=m+1;
////            continue;
//        }
        if(poly_list[m+1].second!=-1)
            count++;
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
        }
//    GLint x1 = poly_list[0].first.x;
//    GLint x2 = poly_list[poly_list.size()-1].first.x;
//    GLint y1 = poly_list[0].first.y;
//    GLint y2 = poly_list[poly_list.size()-1].first.y;
//    GLint deltax,deltay,maxValue,dx,dy;
//    GLint xInc,yInc,xtemp,ytemp;
//    dx=x2-x1;
//    dy=y2-y1;
//    deltax=abs(x2-x1);
//    deltay=abs(y2-y1);
//    if(abs(deltax)>abs(deltay))
//        maxValue = abs(deltax);
//    else
//        maxValue = abs(deltay);

//    int pk,pk1,i;
//    xtemp=x1;
//    ytemp=y1;
//    if(abs(deltay)<abs(deltax)){

//        xInc=0;
//        yInc=0;
//        pk = 2*deltay - deltax;
//        for(i=0;i<=maxValue;i++){
//            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
//            if(dx<0)
//                xInc=-1;
//            else
//                xInc=1;
//            if(pk>=0){
//                pk1=pk+deltay-deltax;
//                pk=pk1;
//                if(dy<0)
//                    yInc=-1;
//                else
//                    yInc=1;
//            }
//            else{
//                pk1=pk+deltay;
//                pk=pk1;
//                yInc=0;
//            }
//            xtemp = xtemp+xInc;
//            ytemp = ytemp+yInc;
//        }
//    }
//    else{
//        xInc=0;
//        yInc=0;
//        pk = 2*deltax - deltay;
//        for(i=0;i<=maxValue;i++){
//            this->points.push_back(make_pair(int(xtemp),int(ytemp)));
//            if(dy<0)
//                yInc=-1;
//            else
//                yInc=1;
//            if(pk>=0){
//                pk1=pk+deltax-deltay;
//                pk=pk1;
//                if(dx<0)
//                    xInc=-1;
//                else
//                    xInc=1;
//            }
//            else{
//                pk1=pk+deltax;
//                pk=pk1;
//                xInc=0;
//            }
//            xtemp = xtemp+xInc;
//            ytemp = ytemp+yInc;
//        }
//    }


}



void Polygon::draw_polygon(point p1,point p2)
{
    if(gl_widget::start_flag==1){
        this->end_points.push_back(make_pair(p1,p2));
    }
    if(gl_widget::same_poly_flag==1&&gl_widget::start_flag==0){
        p1.x = all_objects[all_objects.size()-1]->points[all_objects[all_objects.size()-1]->points.size()-1].first;
        p1.y = all_objects[all_objects.size()-1]->points[all_objects[all_objects.size()-1]->points.size()-1].second;
        this->initial.x = all_objects[all_objects.size()-1]->points[0].first;
        this->initial.y = all_objects[all_objects.size()-1]->points[0].second;
        all_objects[all_objects.size()-1]->end_points.push_back(make_pair(p1,p2));
    }
    if(gl_widget::last_poly_flag==1){
        p1.x = all_objects[all_objects.size()-1]->points[all_objects[all_objects.size()-1]->points.size()-1].first;
        p1.y = all_objects[all_objects.size()-1]->points[all_objects[all_objects.size()-1]->points.size()-1].second;
        p2.x = all_objects[all_objects.size()-1]->points[0].first;
        p2.y = all_objects[all_objects.size()-1]->points[0].second;
        all_objects[all_objects.size()-1]->end_points.push_back(make_pair(p1,p2));
    }


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


}

void Polygon::group()
{
    unsigned i,j;
    unsigned first_index = unsigned(list_obj_index[0]);
//    this->color = all_objects[first_index]->color;
    this->thickness=  all_objects[first_index]->thickness;
    this->color[0]=all_objects[first_index]->color[0];
    this->color[1]=all_objects[first_index]->color[1];
    this->color[2]=all_objects[first_index]->color[2];
    this->color[3]=all_objects[first_index]->color[3];
    this->pattern[0]=all_objects[first_index]->pattern[0];
    this->pattern[1]=all_objects[first_index]->pattern[1];
    this->pattern[2]=all_objects[first_index]->pattern[2];
    this->pattern[3]=all_objects[first_index]->pattern[3];
    this->pattern[4]=all_objects[first_index]->pattern[4];
    this->pattern[5]=all_objects[first_index]->pattern[5];
    this->pattern[6]=all_objects[first_index]->pattern[6];
    this->pattern[7]=all_objects[first_index]->pattern[7];

    for(i=0;i<list_obj_index.size();i++){
        for(j=0;j<all_objects[unsigned(list_obj_index[i])]->points.size();j++){
            this->points.push_back(make_pair(all_objects[unsigned(list_obj_index[i])]->points[j].first,all_objects[unsigned(list_obj_index[i])]->points[j].second));
        }
        all_objects[unsigned(list_obj_index[i])]->points.clear();
    }
    for(i=0;i<all_objects.size();i++){
        if(all_objects[i]->points.size()==0){
            all_objects.erase(all_objects.begin()+i);
            i=i-1;
        }
    }
}

void Polygon::special_polygon(point p1, point p2)
{
    GLint cx = p1.x;
    GLint x = p2.x;
    GLint cy = p1.y;
    GLint y = p2.y;

    GLint radius = pow((x-cx)*(x-cx)+(y-cy)*(y-cy),0.5);
    vector<pair<int,int> > temp_points;
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
    vector <pair<int,int>> poly_vertices;
    int i;
    for(i=0;i<gl_widget::n_vertex;i++){
        double ytemp1,xtemp1;
        double value1 = (radius * cos(2*PI*i/(gl_widget::n_vertex*1)));
        double value2 = (radius * sin(2*PI*i/(gl_widget::n_vertex*1)));
        xtemp1 = cx + value1;
        ytemp1 = cy +value2;
        poly_vertices.push_back(make_pair(xtemp1,ytemp1));

    }
    int j;
    for(i=0;i<gl_widget::n_vertex;i++){
        for(j=i+1;j<gl_widget::n_vertex;j++){
            GLint x1 = poly_vertices[unsigned(i)].first;
            GLint y1 = poly_vertices[unsigned(i)].second;
            GLint x2 = poly_vertices[unsigned(j)].first;
            GLint y2 = poly_vertices[unsigned(j)].second;
            GLint deltax=0,deltay=0,maxValue=0,dx=0,dy=0;
            GLint xInc=0,yInc=0,xtemp=0,ytemp=0;
            dx=x2-x1;
            dy=y2-y1;
            deltax=abs(x2-x1);
            deltay=abs(y2-y1);
            if(abs(deltax)>abs(deltay))
                maxValue = abs(deltax);
            else
                maxValue = abs(deltay);

            int pk=0,pk1=0,i;
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
        }
    }
}
