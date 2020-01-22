#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat image1 = cv::imread("C:/Users/dalbi/Desktop/testPhoto/soustraction1.png", 1);
    cv::imshow("Image 1", image1);
    cv::Mat image2 = cv::imread("C:/Users/dalbi/Desktop/testPhoto/soustraction2.png", 1);
    cv::imshow("Image 2", image2);
    cv::Mat resultat;
    cv::subtract(image1, image2, resultat);
    cv::imshow("Soustraction", resultat);

}

MainWindow::~MainWindow()
{
    delete ui;
}

