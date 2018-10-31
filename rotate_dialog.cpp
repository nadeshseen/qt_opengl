#include "rotate_dialog.h"
#include "ui_rotate_dialog.h"
#include "ui_mainwindow.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
//#include "mainwindow.h"

#include "QDebug"

Rotate_dialog::Rotate_dialog(QWidget *parent,Ui::MainWindow *parent_ui) :
    QDialog(parent),
    rotate_ui(new Ui::Rotate_dialog)
{
    rotate_ui->setupUi(this);
    ok_flag=1;
    rotate_ui->pushButton->hide();
    connect(rotate_ui->pushButton,SIGNAL(released()),parent_ui->widget,SLOT(update()));
    rotate_ui->doubleSpinBox->setRange(-360,360);
}

Rotate_dialog::~Rotate_dialog()
{
    delete rotate_ui;
}

void Rotate_dialog::on_buttonBox_accepted()
{

}


void Rotate_dialog::on_initial_pivot_clicked(bool checked)
{
    if(checked == true){
        rotate_ui->spinBox->setDisabled(true);
        rotate_ui->spinBox_2->setDisabled(true);
        rotate_ui->label_3->setDisabled(true);
        rotate_ui->label_4->setDisabled(true);
    }
}

void Rotate_dialog::on_final_pivot_clicked(bool checked)
{
    if(checked == true){
        rotate_ui->spinBox->setDisabled(true);
        rotate_ui->spinBox_2->setDisabled(true);
        rotate_ui->label_3->setDisabled(true);
        rotate_ui->label_4->setDisabled(true);
    }
}

void Rotate_dialog::on_fixed_point_clicked(bool checked)
{
    if (checked == true){
        rotate_ui->spinBox->setEnabled(true);
        rotate_ui->spinBox_2->setEnabled(true);
        rotate_ui->label_3->setEnabled(true);
        rotate_ui->label_4->setEnabled(true);
    }
}

void Rotate_dialog::on_origin_clicked(bool checked)
{
    if(checked == true){
        rotate_ui->spinBox->setDisabled(true);
        rotate_ui->spinBox_2->setDisabled(true);
        rotate_ui->label_3->setDisabled(true);
        rotate_ui->label_4->setDisabled(true);
    }
}

void Rotate_dialog::on_pushButton_pressed()
{
    double angle = rotate_ui->doubleSpinBox->value();
    point pivot;
    unsigned long index_selected = unsigned(object::index_selected);

    if(Rotate_dialog::ok_flag==1){
        object::transform_object = object::all_objects[object::index_selected];
        Rotate_dialog::ok_flag=0;
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
    if(rotate_ui->initial_pivot->isChecked()==true){
        pivot.x=object::transform_object->initial.x;
        pivot.y=object::transform_object->initial.y;
    }
    else if(rotate_ui->final_pivot->isChecked()==true){
        pivot.x=object::transform_object->final.x;
        pivot.y=object::transform_object->final.y;
    }
    else if (rotate_ui->fixed_point->isChecked()==true){
        pivot.x = rotate_ui->spinBox->value();
        pivot.y = rotate_ui->spinBox_2->value();
    }
    else if (rotate_ui->origin->isChecked()==true){
        pivot.x = 0;
        pivot.y = 0;
    }
    if(object::all_objects[index_selected]->object_name=="Line"){
        line *line_object = new line(pixelSize,object_color,object_pattern);
        line_object->rotate(angle,pivot);
    }
    else if(object::all_objects[index_selected]->object_name=="Circle"){
        circle *circle_object = new circle(pixelSize,object_color,object_pattern);
        circle_object->rotate(angle,pivot);
    }
    else if(object::all_objects[index_selected]->object_name=="Ellipse"){
        Ellipse *ellipse_object = new Ellipse(pixelSize,object_color,object_pattern);
        ellipse_object->rotate(angle,pivot);
    }
}

void Rotate_dialog::on_doubleSpinBox_valueChanged(double arg1)
{
    on_pushButton_pressed();
    rotate_ui->pushButton->released();
}

void Rotate_dialog::on_spinBox_valueChanged(int arg1)
{
    on_pushButton_pressed();
    rotate_ui->pushButton->released();
}

void Rotate_dialog::on_spinBox_2_valueChanged(int arg1)
{
    on_pushButton_pressed();
    rotate_ui->pushButton->released();
}

void Rotate_dialog::on_buttonBox_rejected()
{
    object::all_objects[object::index_selected] = object::transform_object;
}
