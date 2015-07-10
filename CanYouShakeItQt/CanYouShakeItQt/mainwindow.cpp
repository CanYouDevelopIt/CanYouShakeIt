#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shakemanager.h"
#include <QMediaPlayer>
#include <QFileDialog>

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Mp3 Files (*.mp3)"));
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl::fromLocalFile(fileName));

    shakeIt.startGame(music);
}

void MainWindow::on_setParameters_clicked()
{
    shakeIt.setParameters();
}

