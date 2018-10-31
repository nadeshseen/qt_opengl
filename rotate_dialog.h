#ifndef ROTATE_DIALOG_H
#define ROTATE_DIALOG_H
#include"mainwindow.h"
#include <QDialog>

namespace Ui {
class Rotate_dialog;
}

class Rotate_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Rotate_dialog(QWidget *parent = nullptr,Ui::MainWindow *parent_ui = nullptr);
    ~Rotate_dialog();
    static inline int ok_flag=1;
private slots:
    void on_buttonBox_accepted();

    void on_initial_pivot_clicked(bool checked);

    void on_final_pivot_clicked(bool checked);

    void on_fixed_point_clicked(bool checked);

    void on_origin_clicked(bool checked);

    void on_pushButton_pressed();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_buttonBox_rejected();

private:
    Ui::Rotate_dialog *rotate_ui;
};

#endif // ROTATE_DIALOG_H
