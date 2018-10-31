#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "object.h"
#include <vector>
#include <GL/glut.h>

class Translate_dialog;
class pattern_dialog;
class scale_dialog;
class Thickness_Dialog;
class Rotate_dialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_actionExit_triggered();
    void on_actionColor_triggered();
    void on_actionThickness_triggered();
    void on_actionPattern_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionClear_triggered();
    void on_actionSimple_DDA_triggered();
    void on_actionSymmetric_DDA_triggered();
    void on_actionBresenham_triggered();
    void on_actionMid_Point_triggered();
    void on_actionCircle_Mid_Point_triggered();
    void on_actionTranslate_triggered();
    void on_actionScale_triggered();
    void on_actionRotate_triggered();
    void on_actionDelete_triggered();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void on_actionRefresh_triggered();


    void on_actionDetails_triggered();

    void on_actionEllipse_triggered();

    void on_actionFill_triggered();

    void on_actionClip_Window_triggered();

    void on_actionLiang_triggered();

    void on_actionRemove_Clip_Window_triggered();

    void on_actionFlood_Fill_triggered();

    void on_actionGroup_triggered();

    void on_actionPolygon_2_triggered();

    void on_actionSelect_toggled(bool arg1);

    void on_actionSpecial_Polygon_triggered();


    void on_actionIntersection_triggered();

    void on_actionUnion_triggered();

    void on_actionDifference_triggered();

private:
    Thickness_Dialog *thick_dialog;
    pattern_dialog *pattern_box;
    scale_dialog *scale_box;
    Translate_dialog *translate_box;
    Rotate_dialog *rotate_box;
};

extern int value[2];
extern GLubyte object_color[4];
extern GLubyte fill_color[4];
extern int pixelSize;
extern int object_pattern[8];
extern int key_flag;
extern int translate_flag;
extern int fixed_x,fixed_y;
extern int win_height,win_width;
#endif // MAINWINDOW_H
