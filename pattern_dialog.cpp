#include "pattern_dialog.h"
#include "ui_pattern_dialog.h"
#include "QDebug"
#include "mainwindow.h"
pattern_dialog::pattern_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pattern_dialog)
{
    ui->setupUi(this);
}

pattern_dialog::~pattern_dialog()
{
    delete ui;
}

void pattern_dialog::on_pattern_1_clicked(bool checked)
{
    if(checked==true){
        object_pattern[0]=1;
        object_pattern[1]=1;
        object_pattern[2]=1;
        object_pattern[3]=1;
        object_pattern[4]=1;
        object_pattern[5]=1;
        object_pattern[6]=1;
        object_pattern[7]=1;
    }
}

void pattern_dialog::on_pattern_2_clicked(bool checked)
{
    if(checked==true){
        object_pattern[0]=1;
        object_pattern[1]=0;
        object_pattern[2]=0;
        object_pattern[3]=0;
        object_pattern[4]=1;
        object_pattern[5]=0;
        object_pattern[6]=0;
        object_pattern[7]=0;
    }
}

void pattern_dialog::on_pattern_3_clicked(bool checked)
{
    if(checked==true){
        object_pattern[0]=1;
        object_pattern[1]=1;
        object_pattern[2]=1;
        object_pattern[3]=1;
        object_pattern[4]=0;
        object_pattern[5]=0;
        object_pattern[6]=0;
        object_pattern[7]=0;
    }
}

void pattern_dialog::on_pattern_4_clicked(bool checked)
{
    if(checked==true){
        object_pattern[0]=1;
        object_pattern[1]=1;
        object_pattern[2]=0;
        object_pattern[3]=0;
        object_pattern[4]=0;
        object_pattern[5]=0;
        object_pattern[6]=0;
        object_pattern[7]=0;
    }
}

void pattern_dialog::on_buttonBox_accepted()
{
    object::set_pattern(object_pattern);
}
