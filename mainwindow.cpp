#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "special_polygon.h"
#include "translate_dialog.h"
#include "thickness_dialog.h"
#include "pattern_dialog.h"
#include "scale_dialog.h"
#include "rotate_dialog.h"
//#include "object.h"
#include "polygon.h"

//#include<QDebug>
#include<QColor>
#include<QColorDialog>
#include<QMessageBox>
//#include<QShortcut>
int value[2]={0,0};
GLubyte object_color[4]={255,255,255,1};
GLubyte fill_color[4]={255,255,255,1};
int pixelSize=1;
int object_pattern[8]={1,1,1,1,1,1,1,1};


int key_flag=0;
int translate_flag=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionClear,SIGNAL(triggered()),ui->widget,SLOT(update()) );
    connect(ui->actionUndo,SIGNAL(triggered()),ui->widget,SLOT(update()) );
    connect(ui->actionRedo,SIGNAL(triggered()),ui->widget,SLOT(update()) );
    connect(ui->actionTranslate,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionRotate,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionScale,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionDelete,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionTranslate,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionLiang,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionRemove_Clip_Window,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionRefresh,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionPolygon_2,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionIntersection,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionUnion,SIGNAL(triggered()),ui->widget,SLOT(update()));
    connect(ui->actionDifference,SIGNAL(triggered()),ui->widget,SLOT(update()));
//    ui->statusBar->showMessage("Copyright@Nadesh");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color for the object");
    if(color.isValid()){
        object_color[0]=GLubyte(color.red());
        object_color[1]=GLubyte(color.green());
        object_color[2]=GLubyte(color.blue());
        object_color[3]=1;
        value[0]=99;
    }
    object::set_color(object_color);
//    qDebug()<<object_color[0]<<" "<<object_color[1]<<" "<<object_color[2];
}
void MainWindow::on_actionThickness_triggered()
{
//    Thickness_Dialog thick_dialog;
//    thick_dialog.setModal(true);
//    thick_dialog.exec();
    thick_dialog = new Thickness_Dialog(this);
    thick_dialog->show(); //modeless approach

}
void MainWindow::on_actionPattern_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    pattern_box = new pattern_dialog(this);
    pattern_box->show();

}

void MainWindow::on_actionUndo_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    object::undo();
}
void MainWindow::on_actionRedo_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    object::redo();
}
void MainWindow::on_actionClear_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    value[0]=1;
}
void MainWindow::on_actionSimple_DDA_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();

    ui->actionSimple_DDA->setChecked(true);
    value[0]=211;
}

void MainWindow::on_actionSymmetric_DDA_triggered()
{
    value[0]=212;
}

void MainWindow::on_actionBresenham_triggered()
{
    value[0]=213;
}

void MainWindow::on_actionMid_Point_triggered()
{
    value[0]=214;
}

void MainWindow::on_actionCircle_Mid_Point_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    ui->actionCircle_Mid_Point->setChecked(true);
    value[0]=221;
}


void MainWindow::on_actionTranslate_triggered()
{

    if(object::selected_object_num==-1){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
        value[0]=99;
    }else{
        translate_box = new Translate_dialog(this,this->ui);
        translate_box->show();
    }
}

void MainWindow::on_actionScale_triggered()
{
    if(object::index_selected==-1){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
        value[0]=99;
    }else{
        scale_box = new scale_dialog(this,ui);
        scale_box->show();
    }
}

void MainWindow::on_actionRotate_triggered()
{
    if(object::selected_object_num==-1){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
        value[0]=99;
    }else{
        rotate_box = new Rotate_dialog(this,ui);
        rotate_box->show();
//        Rotate_dialog rotate_box;
//        rotate_box.setModal(true);
//        rotate_box.exec();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(object::list_obj_index.size()==0){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }else{
        object::delete_object();
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777249){
        gl_widget::ctrl_key_flag=1;
    }
    if(event->key()==16777220){
        gl_widget::enter_key_flag=1;
    }
    ui->actionRefresh->triggered();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==16777249){
        gl_widget::ctrl_key_flag=0;
    }

}

void MainWindow::on_actionRefresh_triggered()
{
//    ui->widget->update();
}


void MainWindow::on_actionDetails_triggered()
{
//    qDebug()<<"Object Number: "<<object::selected_object_num<<" "<<"Object Index: "<<object::index_selected;

}

void MainWindow::on_actionEllipse_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    ui->actionEllipse->setChecked(true);
    value[0]=231;
}

void MainWindow::on_actionFill_triggered()
{
    if(object::index_selected==-1){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
        value[0]=99;
    }
    else{
            QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color for the object");
            if(color.isValid()){
                fill_color[0]=GLubyte(color.red());
                fill_color[1]=GLubyte(color.green());
                fill_color[2]=GLubyte(color.blue());
                fill_color[3]=GLubyte(color.alpha());
                value[0]=46;
            }
        }
}

void MainWindow::on_actionClip_Window_triggered()
{
    value[0]=240;
}

void MainWindow::on_actionLiang_triggered()
{
    if(gl_widget::clip_window_on==0){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","There is no clip window !");
        messageBox.setFixedSize(500,200);
        value[0]=99;
    }
    else
    {
        value[0]=411;
    }
}

void MainWindow::on_actionRemove_Clip_Window_triggered()
{
    gl_widget::clip_window_on=0;
    gl_widget::clip_points.clear();
    value[0]=value[1];
}

void MainWindow::on_actionFlood_Fill_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color for the object");
    if(color.isValid()){
        fill_color[0]=GLubyte(color.red());
        fill_color[1]=GLubyte(color.green());
        fill_color[2]=GLubyte(color.blue());
        fill_color[3]=1;
        value[0]=47;
    }

}

void MainWindow::on_actionGroup_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(object::list_obj_index.size()==0){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }else{
        Polygon *polygon_object = new Polygon(pixelSize,object_color,object_pattern);
        polygon_object->group();
        object::all_objects.push_back(polygon_object);
        object::temp_objects.clear();
    }
}

void MainWindow::on_actionPolygon_2_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    ui->actionPolygon_2->setChecked(true);
    value[0]=241;

//    on_actionSelect_toggled(false);
}

void MainWindow::on_actionSelect_toggled(bool arg1)
{

    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(arg1==true){
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        value[0]=3;
    }
    else{
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        value[0]=0;
    }
}

void MainWindow::on_actionSpecial_Polygon_triggered()
{
        Special_polygon vertex_dialog;
        vertex_dialog.setModal(true);
        vertex_dialog.exec();
}



void MainWindow::on_actionIntersection_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(object::list_obj_index.size()<2){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }else{
        Polygon *poly_object = new Polygon(pixelSize,object_color,object_pattern);
        poly_object->weiler_atherton(1);
        object::all_objects.push_back(poly_object);
        object::temp_objects.clear();
    }
}

void MainWindow::on_actionUnion_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(object::list_obj_index.size()<2){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }else{
        Polygon *poly_object = new Polygon(pixelSize,object_color,object_pattern);
        poly_object->weiler_atherton(2);
        object::all_objects.push_back(poly_object);
        object::temp_objects.clear();
    }
}

void MainWindow::on_actionDifference_triggered()
{
    if(ui->actionSelect->isChecked())
        ui->actionSelect->toggle();
    if(ui->actionSimple_DDA->isChecked())
        ui->actionSimple_DDA->toggle();
    if(ui->actionCircle_Mid_Point->isChecked())
        ui->actionCircle_Mid_Point->toggle();
    if(ui->actionEllipse->isChecked())
        ui->actionEllipse->toggle();
    if(ui->actionPolygon_2->isChecked())
        ui->actionPolygon_2->toggle();
    if(object::list_obj_index.size()<2){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }else{
        Polygon *poly_object = new Polygon(pixelSize,object_color,object_pattern);
        poly_object->weiler_atherton(3);
        object::all_objects.push_back(poly_object);
        object::temp_objects.clear();
    }
}
