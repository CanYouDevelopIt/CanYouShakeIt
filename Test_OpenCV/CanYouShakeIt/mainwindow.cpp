#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include "shakemanager.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonDisplayImage_clicked()
{
    char * imageDir = "C://Users//Yolo//Desktop//raio.jpg";
    Mat image = imread(imageDir);
    if(!image.data)
    {
        cout << "Image Loading error."<<endl;
        return;
    }
    namedWindow("TestImage", WINDOW_AUTOSIZE);
    imshow("TestImage",image);
    waitKey();
    destroyWindow("TestImage");

}

void MainWindow::on_LancerCanYouShakeIt_clicked()
{
      ShakeManager shakeIt;
      shakeIt.launchApplication();
}
