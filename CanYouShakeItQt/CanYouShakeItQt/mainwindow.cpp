#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shakemanager.h"

ShakeManager shakeIt;

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

void MainWindow::on_start_clicked()
{
    shakeIt.startGame();
}

void MainWindow::on_setParameters_clicked()
{
    shakeIt.setParameters();
}
