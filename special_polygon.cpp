#include "special_polygon.h"
#include "ui_special_polygon.h"
#include<QtDebug>
Special_polygon::Special_polygon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Special_polygon)
{
    ui->setupUi(this);
    ui->vertices->setValue(5);
}

Special_polygon::~Special_polygon()
{
    delete ui;
}

void Special_polygon::on_buttonBox_accepted()
{
    gl_widget::n_vertex = ui->vertices->value();
    value[0]=251;
//    qDebug()<<gl_widget::n_vertex;
}
