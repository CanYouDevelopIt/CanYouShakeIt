#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shakemanager.h"

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
    ShakeManager shakeIt;
    shakeIt.startGame();
}
