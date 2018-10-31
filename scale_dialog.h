#ifndef SCALE_DIALOG_H
#define SCALE_DIALOG_H
#include"mainwindow.h"
#include <QDialog>

namespace Ui {
class scale_dialog;
}

class scale_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit scale_dialog(QWidget *parent = nullptr,Ui::MainWindow *parent_ui = nullptr);
    ~scale_dialog();
    static inline int temp_object_flag=1;

private slots:

    void on_buttonBox_accepted();

    void on_fixed_point_clicked(bool checked);

    void on_origin_clicked(bool checked);

    void on_initial_pivot_clicked(bool checked);

    void on_final_pivot_clicked(bool checked);

    void on_pushButton_pressed();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_buttonBox_rejected();

private:
    Ui::scale_dialog *scale_ui;
};

#endif // SCALE_DIALOG_H
