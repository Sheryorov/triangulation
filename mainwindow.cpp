#include <cmath>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawarea.h"
#include <QFileDialog>
#include "triFunc.h"
#include "scala.h"

MainWindow* mainWindow = 0;
DrawArea* drawArea = 0;

static double f(const R2Point&);

static double f(const R2Point& p) {
    double r = R2Point(0., 0.).distance(p);
    return 2.*cos(4.*r)/(1. + 0.2*r*r);
}

static double f3D(const R3Point&);

static double f3D(const R3Point& p) {

    // double R = R3Point(0., 0., 0.).distance(p);
    // return R - 3.;

    // return (p.x*p.y - p.z);

    R2Point q(p.x, p.y);
    double r = R2Point(0., 0.).distance(q);
    return 2.*cos(4.*r)/(1. + 0.2*r*r) - p.z;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    triangulationPath(),
    xMin(-8.),
    xMax(8.),
    yMin(-8.),
    yMax(8.),
    zMin(-8.),
    zMax(8.),
    ui(new Ui::MainWindow)
{
    mainWindow = this;
    ui->setupUi(this);

    QString tmp;
    ui->xMin->setText(tmp.sprintf("%.2f", xMin));
    ui->xMax->setText(tmp.sprintf("%.2f", xMax));
    ui->yMin->setText(tmp.sprintf("%.2f", yMin));
    ui->yMax->setText(tmp.sprintf("%.2f", yMax));
    ui->zMin->setText(tmp.sprintf("%.2f", zMin));
    ui->zMax->setText(tmp.sprintf("%.2f", zMax));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_path_returnPressed()
{
    triangulationPath = ui->path->text();
    on_loadButton_clicked();
}

void MainWindow::on_browseButton_clicked()
{
    QFileDialog openFileDlg;
    QString fileName = QFileDialog::getOpenFileName(
        this, QString("Triangulation File")
    );
    if (fileName == QString())
        return;
    ui->path->setText(fileName);
    //... on_loadButton_clicked();
}

void MainWindow::on_loadButton_clicked() {
    triangulationPath = ui->path->text();
    drawArea->triangulation.load(
        triangulationPath.toStdString().c_str()
    );
    drawArea->update();
}

void MainWindow::on_plot2DButton_clicked()
{
    setCoordinates();
    plot3DFunction(
        &f,
        R2Rectangle(
            R2Point(xMin, yMin),
            xMax - xMin, yMax - yMin
        ),
        128, 128,
        drawArea->triangulation
    );
    drawArea->update();
}

void MainWindow::on_saveButton_clicked()
{
    triangulationPath = ui->path->text();
    if (triangulationPath == "")
        return;
    drawArea->triangulation.save(
        triangulationPath.toStdString().c_str()
    );
}

void MainWindow::on_plot3DButton_clicked()
{
    setCursor(QCursor(Qt::WaitCursor));
    setCoordinates();
    double ymin = xMin;
    double ymax = xMax;
    double zmin = xMin;
    double zmax = xMax;

    scalaMethod(
        &f3D,
        R3Box(
            R3Point(xMin, ymin, zmin),
            R3Vector(
                xMax-xMin, ymax-ymin, zmax-zmin
            )
        ),
        64, 64, 64,
        drawArea->triangulation
    );
    setCursor(QCursor(Qt::ArrowCursor));
    drawArea->update();
}

void MainWindow::on_redrawButton_clicked()
{
    setCoordinates();
    drawArea->update();
}

void MainWindow::setCoordinates() {
    xMin = ui->xMin->text().toDouble();
    xMax = ui->xMax->text().toDouble();
    yMin = ui->yMin->text().toDouble();
    yMax = ui->yMax->text().toDouble();
    zMin = ui->zMin->text().toDouble();
    zMax = ui->zMax->text().toDouble();
    double dx = fabs(xMax - xMin)*1.2;
    double xCenter = (xMax + xMin)/2.;
    drawArea->xmin = xCenter - dx/2.;
    drawArea->xmax = xCenter + dx/2.;
    drawArea->onResizeGL();
}
