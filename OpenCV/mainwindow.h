#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


private:
    Ui::MainWindow *ui;

    //Chargement et affichage de l'image
    Mat image2 = imread("C:/Users/dalbi/Desktop/testPhoto/test1.jpg", IMREAD_COLOR);
    Mat grey;

    //Hough Transform
    vector<Vec3f> circles;

    //Variables tracés cercles
    size_t i;
    Vec3i c;
    Point center;
    int radius;

    //Variables position
    int x;
    int y;
};
#endif // MAINWINDOW_H
