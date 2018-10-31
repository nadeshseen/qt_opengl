#include "scale_dialog.h"
#include "ui_scale_dialog.h"
#include "ui_mainwindow.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include<QDebug>
scale_dialog::scale_dialog(QWidget *parent,Ui::MainWindow *parent_ui) :
    QDialog(parent),
    scale_ui(new Ui::scale_dialog)
{
    scale_ui->setupUi(this);
    this->setWindowTitle("Scale");
    temp_object_flag=1;
    scale_ui->pushButton->hide();
    connect(scale_ui->pushButton,SIGNAL(released()),parent_ui->widget,SLOT(update()));
    scale_ui->doubleSpinBox->setValue(1);
    scale_ui->doubleSpinBox_2->setValue(1);
    scale_ui->doubleSpinBox->setSingleStep(0.1);
    scale_ui->doubleSpinBox_2->setSingleStep(0.1);
    scale_ui->spinBox->setRange(-10000,10000);
    scale_ui->spinBox_2->setRange(-10000,10000);
}

scale_dialog::~scale_dialog()
{
    delete scale_ui;
}

void scale_dialog::on_buttonBox_accepted()
{
}


void scale_dialog::on_fixed_point_clicked(bool checked)
{
    if (checked == true){
        scale_ui->spinBox->setEnabled(true);
        scale_ui->spinBox_2->setEnabled(true);
        scale_ui->label_4->setEnabled(true);
        scale_ui->label_5->setEnabled(true);

        scale_ui->spinBox->setValue(fixed_x);
        scale_ui->spinBox_2->setValue(fixed_y);

    }
}

void scale_dialog::on_origin_clicked(bool checked)
{
    if(checked == true){

        scale_ui->spinBox->setDisabled(true);
        scale_ui->spinBox_2->setDisabled(true);
        scale_ui->label_4->setDisabled(true);
        scale_ui->label_5->setDisabled(true);
    }
}

void scale_dialog::on_initial_pivot_clicked(bool checked)
{
    if(checked == true){

        scale_ui->spinBox->setDisabled(true);
        scale_ui->spinBox_2->setDisabled(true);
        scale_ui->label_4->setDisabled(true);
        scale_ui->label_5->setDisabled(true);
    }
}

void scale_dialog::on_final_pivot_clicked(bool checked)
{
    if(checked == true){

        scale_ui->spinBox->setDisabled(true);
        scale_ui->spinBox_2->setDisabled(true);
        scale_ui->label_4->setDisabled(true);
        scale_ui->label_5->setDisabled(true);
    }
}

void scale_dialog::on_pushButton_pressed()
{
    scale_struct scale;
    scale.x = scale_ui->doubleSpinBox->value();
    scale.y = scale_ui->doubleSpinBox_2->value();
    point pivot;
    unsigned long index_selected = unsigned(object::index_selected);

    if(scale_dialog::temp_object_flag==1){
        object::transform_object = object::all_objects[object::index_selected];
        scale_dialog::temp_object_flag=0;
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
    if(scale_ui->initial_pivot->isChecked()==true){
        pivot.x=object::transform_object->initial.x;
        pivot.y=object::transform_object->initial.y;
    }
    else if(scale_ui->final_pivot->isChecked()==true){
        pivot.x=object::transform_object->final.x;
        pivot.y=object::transform_object->final.y;
    }
    else if (scale_ui->fixed_point->isChecked()==true){
        pivot.x = scale_ui->spinBox->value();
        pivot.y = scale_ui->spinBox_2->value();
    }
    else if (scale_ui->origin->isChecked()==true){
        pivot.x = 0;
        pivot.y = 0;
    }
    if(object::all_objects[index_selected]->object_name=="Line"){
        line *line_object = new line(pixelSize,object_color,object_pattern);
        line_object->scale(scale,pivot);
    }
    else if(object::all_objects[index_selected]->object_name=="Circle"){
        circle *circle_object = new circle(pixelSize,object_color,object_pattern);
        circle_object->scale(scale,pivot);
    }
    else if(object::all_objects[index_selected]->object_name=="Ellipse"){
        Ellipse *ellipse_object = new Ellipse(pixelSize,object_color,object_pattern);
        ellipse_object->scale(scale,pivot);
    }
}

void scale_dialog::on_doubleSpinBox_valueChanged(double arg1)
{
    on_pushButton_pressed();
    scale_ui->pushButton->released();
}

void scale_dialog::on_doubleSpinBox_2_valueChanged(double arg1)
{
    on_pushButton_pressed();
    scale_ui->pushButton->released();
}

void scale_dialog::on_spinBox_valueChanged(int arg1)
{
    on_pushButton_pressed();
    scale_ui->pushButton->released();
}

void scale_dialog::on_spinBox_2_valueChanged(int arg1)
{
    on_pushButton_pressed();
    scale_ui->pushButton->released();
}

void scale_dialog::on_buttonBox_rejected()
{
    object::all_objects[object::index_selected] = object::transform_object;
}
