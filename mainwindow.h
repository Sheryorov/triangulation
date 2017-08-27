#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DrawArea;
class MainWindow;

extern MainWindow* mainWindow;
extern DrawArea* drawArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString triangulationPath;
    bool loadTriangulation(QString path);

    double xMin, xMax, yMin, yMax, zMin, zMax;

    explicit MainWindow(QWidget *parent = 0);
    void setCoordinates();
    ~MainWindow();

private slots:
    void on_path_returnPressed();

    void on_browseButton_clicked();

    void on_loadButton_clicked();

    void on_plot2DButton_clicked();

    void on_saveButton_clicked();

    void on_plot3DButton_clicked();

    void on_redrawButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
