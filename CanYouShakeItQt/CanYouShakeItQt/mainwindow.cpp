#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shakemanager.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QListWidget>
#include <QtSql>

ShakeManager shakeIt;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadPlayer();
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

void MainWindow::loadPlayer(){
    std::cout << "LoadTaMere" << std::endl;
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString s = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(s);

    if(mydb.open()) {
        QSqlQuery query("SELECT * FROM joueur");
            while (query.next()) {
                QString id = query.value(0).toString();
                QString joueur = query.value(1).toString();
                std::cout << id.toStdString() << std::endl;
                std::cout << joueur.toStdString() << std::endl;
                ui->listWidget->addItem(joueur);
            }
    }


}

