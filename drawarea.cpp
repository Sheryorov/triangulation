#include <QMouseEvent>
#include <cassert>
#include <cmath>
#include "drawarea.h"
#include "mainwindow.h"
//... #include "GL/glu.h"

DrawArea::DrawArea(QWidget *parent):
    QGLWidget(parent),
    xmin(-8.),
    xmax(8.),
    ymin(-6.),
    ymax(6.),
    alpha(ALPHA0),
    beta(BETA0),
    mouseX(-1),     // Undefined
    mouseY(-1)      // Undefined
{
    setMouseTracking(true);
    drawArea = this;
}

void DrawArea::initializeGL() {
    /*
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0., 0.1, 0.2, 1.);
    */

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LEQUAL);

    // Lighting
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    GLfloat pos[4];
    pos[0] = 0.; pos[1] = 0.; pos[2] = 1.; pos[3] = 0.; // Directional light
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    GLfloat light[4];
    light[0] = 0.25; light[1] = 0.25; light[2] = 0.25; light[3] = 1.;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light);

    light[0] = 1.; light[1] = 1.; light[2] = 1.; light[3] = 1.;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DrawArea::resizeGL(int w, int h) {
    onResizeGL(w, h);
}

void DrawArea::onResizeGL(int w /* = (-1) */, int h /* = (-1) */) {
    if (w < 0) {
        w = width();
        h = height();
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w == 0)
        w = 1;
    if (h == 0)
        h = 1;
    double aspect = (double) w / (double) h;
    assert(aspect > 0.);

    ymin = xmin / aspect;
    ymax = (-ymin);
    double depth = ymax - ymin;
    glOrtho(
        xmin, xmax,
        ymin, ymax,
        -10. * depth, 10. * depth
    );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawArea::paintGL() {
    // Rotate the scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHT0);        // Turn on the first light source

    // Rotate a model
    glRotatef(beta, 1., 0., 0.);
    glRotatef(alpha, 0., 1., 0.);

    render();           // Draw a scene graph

    // swapBuffers();   // Not needed - done automatically
}

void DrawArea::mousePressEvent(QMouseEvent * /* event */) {
    mouseX = (-1);      // Undefined
    mouseY = (-1);      // Undefined
}

void DrawArea::mouseReleaseEvent(QMouseEvent * /* event */) {
    mouseX = (-1);      // Undefined
    mouseY = (-1);      // Undefined
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    //... printf("%d, %d\n", event->x(), event->y());
    int x = event->x();
    int y = event->y();
    if ((event->buttons() & Qt::LeftButton) != 0) {
        if (mouseX >= 0) {
            int dx = x - mouseX;
            int dy = y - mouseY;
            if (beta > 100. || beta < (-100.))
                dx = -dx;

            alpha += dx * 0.1;
            if (fabs(alpha) > 360.)
                alpha -= ((int) alpha / 360) * 360.;

            beta += dy * 0.1;
            if (fabs(beta) > 360.)
                beta -= ((int) beta / 360) * 360.;

            repaint();
        }
        mouseX = x; mouseY = y;

    } else {
        mouseX = (-1);      // Undefined
        mouseY = (-1);      // Undefined
    }
}

void DrawArea::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Escape:
    case Qt::Key_Q:
        close();
        break;
    case Qt::Key_Space:
        alpha = ALPHA0;
        beta = BETA0;
        repaint();
        break;
    default:
        event->ignore();
        break;
    }
}

void DrawArea::render() {
    GLfloat color[4];

    glClearColor(0.1, 0.2, 0.4, 1.); // Background color: dark blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    color[0] = 0.5; color[1] = 1.; color[2] = 0.5;  // Green
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    // Draw the triangualtion
    glBegin(GL_TRIANGLES);
        for (
            size_t t = 0;
            t < triangulation.triangles.size();
            ++t
        ) {
            const Triangulation::Triangle& tr =
                triangulation.triangles[t];

            for (int i = 0; i < 3; ++i) {
                int vertexIdx = tr[i];
                const Triangulation::Vertex& v =
                    triangulation.vertices[vertexIdx];
                // Set a normal to the current point
                glNormal3f(
                    v.normal.x, v.normal.y, v.normal.z
                );
                glVertex3f(
                    v.point.x, v.point.y, v.point.z
                );
            }
        }
    glEnd();

}
