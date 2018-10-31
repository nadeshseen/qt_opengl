#ifndef PATTERN_DIALOG_H
#define PATTERN_DIALOG_H

#include <QDialog>

namespace Ui {
class pattern_dialog;
}

class pattern_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit pattern_dialog(QWidget *parent = nullptr);
    ~pattern_dialog();

private slots:
    void on_pattern_1_clicked(bool checked);

    void on_pattern_2_clicked(bool checked);

    void on_pattern_3_clicked(bool checked);

    void on_pattern_4_clicked(bool checked);

    void on_buttonBox_accepted();

private:
    Ui::pattern_dialog *ui;
};

#endif // PATTERN_DIALOG_H
