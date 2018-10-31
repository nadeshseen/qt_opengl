#include "translate_dialog.h"
#include "ui_translate_dialog.h"
#include "ui_mainwindow.h"

#include "line.h"
#include "circle.h"
#include "ellipse.h"

#include<QDebug>
Translate_dialog::Translate_dialog(QWidget *parent,Ui::MainWindow *parent_ui) :
    QDialog(parent),
    translate_ui(new Ui::Translate_dialog)
{
    translate_ui->setupUi(this);
    this->setWindowTitle("Choose");
    temp_parent=parent_ui;
    ok_flag=1;
    connect(translate_ui->pushButton,SIGNAL(released()),parent_ui->widget,SLOT(update()));
    translate_ui->pushButton->hide();
    translate_ui->spinBox->setRange(-10000,10000);
    translate_ui->spinBox_2->setRange(-10000,10000);
    translate_ui->spinBox_3->setRange(-10000,10000);
    translate_ui->spinBox_4->setRange(-10000,10000);

}

Translate_dialog::~Translate_dialog()
{
    delete translate_ui;
}

void Translate_dialog::on_initial_pivot_clicked(bool checked)
{
    if(checked == true){

        translate_ui->spinBox->setDisabled(true);
        translate_ui->spinBox_2->setDisabled(true);
        translate_ui->label_2->setDisabled(true);
        translate_ui->label_3->setDisabled(true);
    }
}

void Translate_dialog::on_final_pivot_clicked(bool checked)
{
    if(checked == true){

        translate_ui->spinBox->setDisabled(true);
        translate_ui->spinBox_2->setDisabled(true);
        translate_ui->label_2->setDisabled(true);
        translate_ui->label_3->setDisabled(true);
    }
}

void Translate_dialog::on_fixed_point_clicked(bool checked)
{
    if(checked == true){

        translate_ui->spinBox->setEnabled(true);
        translate_ui->spinBox_2->setEnabled(true);
        translate_ui->label_2->setEnabled(true);
        translate_ui->label_3->setEnabled(true);
        translate_ui->spinBox->setValue(fixed_x);
        translate_ui->spinBox_2->setValue(fixed_y);
    }
}

void Translate_dialog::on_origin_clicked(bool checked)
{
    if(checked == true){

        translate_ui->spinBox->setDisabled(true);
        translate_ui->spinBox_2->setDisabled(true);
        translate_ui->label_2->setDisabled(true);
        translate_ui->label_3->setDisabled(true);
    }
}

void Translate_dialog::on_buttonBox_accepted()
{

}


void Translate_dialog::on_pushButton_pressed()
{
//    qDebug()<<object::selected_object_num;
    translate_point.x = translate_ui->spinBox_4->value();
    translate_point.y = translate_ui->spinBox_3->value();
    unsigned long index_selected = unsigned(object::index_selected);
    if(Translate_dialog::ok_flag==1){
        object::transform_object = object::all_objects[object::index_selected];

        Translate_dialog::ok_flag=0;
    }
    pixelSize = object::all_objects[index_selected]->thickness;
    object_color[0] = object::all_objects[index_selected]->color[0];
    object_color[1] = object::all_objects[index_selected]->color[1];
    object_color[2] = object::all_objects[index_selected]->color[2];
    object_color[3] = object::all_objects[index_selected]->color[3];
    object_pattern[0] = object::all_objects[index_selected]->pattern[0];
    object_pattern[1] = object::all_objects[index_selected]->pattern[1];
    object_pattern[2] = object::all_objects[index_selected]->pattern[2];
    object_pattern[3] = object::all_objects[index_selected]->pattern[3];
    object_pattern[4] = object::all_objects[index_selected]->pattern[4];
    object_pattern[5] = object::all_objects[index_selected]->pattern[5];
    object_pattern[6] = object::all_objects[index_selected]->pattern[6];
    object_pattern[7] = object::all_objects[index_selected]->pattern[7];

    if(object::all_objects[index_selected]->object_name=="Line"){
        line *line_object = new line(pixelSize,object_color,object_pattern);
        line_object->translate(translate_point);
    }
    else if(object::all_objects[index_selected]->object_name=="Circle"){
        circle *circle_object = new circle(pixelSize,object_color,object_pattern);
        circle_object->translate(translate_point);
    }
    else if(object::all_objects[index_selected]->object_name=="Ellipse"){
        Ellipse *ellipse_object = new Ellipse(pixelSize,object_color,object_pattern);
        ellipse_object->translate(translate_point);
    }
}

void Translate_dialog::on_spinBox_4_valueChanged(int arg1)
{
    on_pushButton_pressed();
    translate_ui->pushButton->released();
//    temp_parent->widget->update();
}

void Translate_dialog::on_spinBox_3_valueChanged(int arg1)
{
    on_pushButton_pressed();
    translate_ui->pushButton->released();
}

void Translate_dialog::on_buttonBox_rejected()
{
    object::all_objects[object::index_selected] = object::transform_object;
}



