#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Chargement et affichage de l'image
    Mat image2 = imread("C:/Users/dalbi/Desktop/testPhoto/test.jpg", IMREAD_COLOR);

    if(image2.empty()){
        qDebug() << "Erreur chargement image";
    }

    //Convertion en echelle de gris
    Mat grey;
    cvtColor(image2, grey, cv::COLOR_BGR2GRAY);

    //Application de flou pour réduire le bruit
    medianBlur(grey, grey, 5);

    //Application de la transformation de cercle de Hough
    vector<Vec3f> circles;
    HoughCircles(grey, circles, HOUGH_GRADIENT, 1, grey.rows/1, 100, 20, 0, 0);

    //Préparation des cercles détectés
    for (size_t i = 0; i < circles.size(); i++){
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        //Centre du cercle
        circle(image2, center, 1, Scalar(0,100,100), 3, LINE_AA);
        //Bordue du cercle
        int radius = c[2];
        circle(image2, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }

    //Affichage des cercles détectés
    imshow("detected circles", image2);
    int x = circles[0][0];
    int y = circles[0][1];
    qDebug() << x << " " << y;

}

MainWindow::~MainWindow()
{
    delete ui;
}

