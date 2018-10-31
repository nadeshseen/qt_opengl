#ifndef SPECIAL_POLYGON_H
#define SPECIAL_POLYGON_H
#include"mainwindow.h"
#include <QDialog>

namespace Ui {
class Special_polygon;
}

class Special_polygon : public QDialog
{
    Q_OBJECT

public:
    explicit Special_polygon(QWidget *parent = nullptr);
    ~Special_polygon();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Special_polygon *ui;
};

#endif // SPECIAL_POLYGON_H
