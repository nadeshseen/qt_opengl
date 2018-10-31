#ifndef THICKNESS_DIALOG_H
#define THICKNESS_DIALOG_H

#include <QDialog>

namespace Ui {
class Thickness_Dialog;
}

class Thickness_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Thickness_Dialog(QWidget *parent = nullptr);
    ~Thickness_Dialog();

private slots:

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

    void on_buttonBox_accepted();

private:
    Ui::Thickness_Dialog *ui;
};

#endif // THICKNESS_DIALOG_H
