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

    //Si l'image n'est pas lu, on renvoie une erreur
    if(image2.empty()){
        qDebug() << "Erreur chargement image";
    }

    //Resize de la photo
    cv::resize(image2, image2, cv::Size(), 0.25, 0.25);

    //Change le contraste
    //threshold(image2, grey, *valeurContraste, 255, THRESH_BINARY_INV); //THRESH_BINARY
    //imshow("Contrasted image", grey);

    //Convertie en echelle de gris
    cvtColor(image2, grey, cv::COLOR_BGR2GRAY);

    //Application de flou pour réduire le bruit
    medianBlur(grey, grey, 5);
    //imshow("Gris + Blur", grey);

    //Application de la transformation de cercle de Hough
    HoughCircles(grey, circles, HOUGH_GRADIENT, 1, grey.rows/ 0.5, 250, 1, 0, 75);

    //Préparation des cercles détectés
    for (i = 0; i < circles.size(); i++){
        c = circles[i];
        center = Point(c[0], c[1]);
        //Centre du cercle
        circle(image2, center, 1, Scalar(100,100,100), 3, LINE_AA);
        //Bordue du cercle
        radius = c[2];
        circle(image2, center, radius, Scalar(0,255,255), 3, LINE_AA);
    }

    //Affichage des positions des cercles détectés
    imshow("Detected circles", image2);
    x = circles[0][0];
    y = circles[0][1];
    qDebug() << x << " " << y;
}

MainWindow::~MainWindow()
{
    delete ui;
}
