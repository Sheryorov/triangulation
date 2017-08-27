#ifndef _GLWIDGET_H
#define _GLWIDGET_H

// #include <QOpenGLFunctions_1_1>
#include <QtOpenGL/QGLWidget>
// #include <GL/gl.h>
//... #include <GL/glu.h>

#include "Triangulation.h"

const double ALPHA0 = 0.; //(-10.);
const double BETA0 = -60.;  // (-7.);

class DrawArea: public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    DrawArea(QWidget *parent = NULL);

    Triangulation triangulation;

    double xmin, xmax, ymin, ymax;  // Coordinates in window
    double alpha, beta;         // Angles of rotation
    int mouseX, mouseY;         // Previous mouse position
    //... GLUquadricObj*  quadric;    // Quadric object used to draw a sphere

    void onResizeGL(int w = (-1), int h = (-1));

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void render();
};

#endif  /* _GLWIDGET_H */
