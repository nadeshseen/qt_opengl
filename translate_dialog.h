#ifndef TRANSLATE_DIALOG_H
#define TRANSLATE_DIALOG_H
#include"mainwindow.h"
#include <QDialog>
//class MainWindow;

namespace Ui {
class Translate_dialog;
}

class Translate_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Translate_dialog(QWidget *parent = nullptr,Ui::MainWindow *parent_ui = nullptr);
    ~Translate_dialog();
    static inline int ok_flag=1;
    Ui::MainWindow *temp_parent;
//    using QDialog::connect;
//    using QDialog::setWindowTitle;

private slots:
    void on_initial_pivot_clicked(bool checked);

    void on_final_pivot_clicked(bool checked);

    void on_fixed_point_clicked(bool checked);

    void on_origin_clicked(bool checked);

    void on_buttonBox_accepted();

    void on_pushButton_pressed();

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_buttonBox_rejected();

private:
    Ui::Translate_dialog *translate_ui;
};

#endif // TRANSLATE_DIALOG_H
