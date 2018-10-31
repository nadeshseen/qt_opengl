#include "thickness_dialog.h"
#include "ui_thickness_dialog.h"
#include "QDebug"
#include "mainwindow.h"

Thickness_Dialog::Thickness_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Thickness_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Thickness");
//    ui->widget;
}

Thickness_Dialog::~Thickness_Dialog()
{
    delete ui;
}


void Thickness_Dialog::on_radioButton_clicked(bool checked)
{
    if(checked==true){
        pixelSize = 1;
    }
}

void Thickness_Dialog::on_radioButton_2_clicked(bool checked)
{
    if(checked==true){
        pixelSize = 2;
    }
}


void Thickness_Dialog::on_radioButton_3_clicked(bool checked)
{
    if(checked==true){
        pixelSize = 3;
    }
}

void Thickness_Dialog::on_radioButton_4_clicked(bool checked)
{
    if(checked==true){
        pixelSize = 4;
    }
}

void Thickness_Dialog::on_buttonBox_accepted()
{
    object::set_thickness(pixelSize);
}
