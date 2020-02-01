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

   //Variables pour les sliders + sliders
    greyRow = new int;
    *greyRow = ui->slider1->value();
    cannyEdgeThreshold = new int;
    *cannyEdgeThreshold = ui->slider2->value();
    centerDetectionTreshold = new int;
    *centerDetectionTreshold = ui->slider3->value();
    valeurContraste = new int;
    *valeurContraste = ui->slider4->value();

    //Si l'image n'est pas lu, on renvoie une erreur
    if(image2.empty()){
        qDebug() << "Erreur chargement image";
    }
    recalculer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_slider1_valueChanged(int value)
{
    *greyRow = value;
}

void MainWindow::on_slider2_valueChanged(int value)
{
    *cannyEdgeThreshold = value;
}

void MainWindow::on_slider3_valueChanged(int value)
{
    *centerDetectionTreshold = value;
}

void MainWindow::on_slider4_valueChanged(int value)
{
    *valeurContraste = value;
}

void MainWindow::on_pushButton_clicked()
{
    recalculer();
}

void MainWindow::recalculer()
{
    //Change le contraste
    threshold(image2, grey, *valeurContraste, 255, THRESH_BINARY_INV); //THRESH_BINARY
    imshow("Contraste", grey);

    //Convertie en echelle de gris
    cvtColor(image2, grey, cv::COLOR_BGR2GRAY);

    //Application de flou pour réduire le bruit
    medianBlur(grey, grey, 5);
    //imshow("Gris + Blur", grey);

    //Application de la transformation de cercle de Hough
    HoughCircles(grey, circles, HOUGH_GRADIENT, 1, grey.rows/ *greyRow, *cannyEdgeThreshold, *centerDetectionTreshold, 0, 0);

    //Préparation des cercles détectés
    for (i = 0; i < circles.size(); i++){
        c = circles[i];
        center = Point(c[0], c[1]);
        //Centre du cercle
        circle(image2, center, 1, Scalar(0,100,100), 3, LINE_AA);
        //Bordue du cercle
        radius = c[2];
        circle(image2, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }

    //Affichage des positions des cercles détectés
    //imshow("detected circles", image2);
    x = circles[0][0];
    y = circles[0][1];
    qDebug() << x << " " << y;
}
