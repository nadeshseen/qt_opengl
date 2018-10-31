#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
struct point{
   GLint x,y;
};
extern point p1,p2,translate_point,selected_point,ecenter,px,py;
//class Polygon;

class gl_widget : public QOpenGLWidget
{
public:
    gl_widget(QWidget *parent=nullptr);
    static int x_at_press,y_at_press,x_at_release,y_at_release;
    static inline int mouse=0,emouse=0;
    static inline int testing_flag=0;
    static inline int clip_window_on=0;
    static inline std::vector <point > clip_points;
    static inline int ctrl_key_flag = 0;
    static inline int enter_key_flag = 0;
    static inline int multi_obj_flag = 0;
    static inline int same_poly_flag = 0;
    static inline int last_poly_flag = 0;

    static inline int start_flag=1;

    static inline int n_vertex=0;
//    static inline Polygon *polygon_object;
    void initializeGL();
    void paintGL();
//    void resizeGL(int w, int h);

    void axis();
    void refresh2d();
    static void draw_points(int x,int y);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void clip_window();

};

#endif // GL_WIDGET_H
