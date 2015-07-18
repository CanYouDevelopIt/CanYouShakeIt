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
    loadPlayers();
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

    QListWidgetItem *item = ui->listWidget->currentItem();

    if(item != nullptr){

        String nomJoueur = item->text().toStdString();
        std::cout << "test : " << nomJoueur << std::endl;

        Joueur *joueur;

        for(Joueur *j : joueurs)
            if(j->getNomJoueur() == nomJoueur)
                joueur = j;

        if(joueur != nullptr)
            shakeIt.startGame(joueur,music);

    }else{
        std::cout << "Erreur" <<std::endl;
    }
}

void MainWindow::on_setParameters_clicked()
{
    shakeIt.setParameters();
}

void MainWindow::loadPlayers(){
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString s = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(s);

    if(mydb.open()) {
        QSqlQuery query("SELECT * FROM joueur");
            while (query.next()) {
                int id = query.value(0).toInt();
                QString joueur = query.value(1).toString();
                int h = query.value(2).toInt();
                int s = query.value(3).toInt();
                int v = query.value(4).toInt();

                Joueur *j = new Joueur(id,joueur.toStdString(),h,s,v);
                joueurs.push_back(j);

                ui->listWidget->addItem(joueur);
            }
    }
}
