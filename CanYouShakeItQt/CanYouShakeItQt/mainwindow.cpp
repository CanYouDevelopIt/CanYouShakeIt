#include "mainwindow.h"
#include "ui_mainwindow.h"

ShakeManager shakeIt;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadPlayers();
    loadBestScores();
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

    QStringList myStringList = fileName.split('/').last().split('/');
    string nomPiste = myStringList.first().toStdString();

    QListWidgetItem *item = ui->listJoueurs->currentItem();

    if(item != nullptr){

        ui->labelSelectJoueur->clear();

        String nomJoueur = item->text().toStdString();
        Joueur *joueur;

        for(Joueur *j : joueurs)
            if(j->getNomJoueur() == nomJoueur)
                joueur = j;

        if(joueur != nullptr){
            shakeIt.startGame(joueur,music,nomPiste);
            QString qNomPiste = QString::fromStdString(nomPiste);
            loadPisteScores(qNomPiste);
        }

    }else{
        ui->labelSelectJoueur->setText("Veuillez sélectionner un joueur");
    }
}

void MainWindow::on_setParameters_clicked()
{
    string newName = ui->nouveauJoueur->toPlainText().toStdString();
    if(!newName.empty()){
        shakeIt.setParameters(newName);
        loadPlayers();
    }else{
        ui->enterNameLabel->setText(" Entrez un nom ");
    }
}

void MainWindow::loadPlayers(){
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString s = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(s);

    if(mydb.open()) {
        joueurs.clear();
        ui->listJoueurs->clear();

        QSqlQuery query("SELECT * FROM joueur");
            while (query.next()) {
                int id = query.value(0).toInt();
                QString joueur = query.value(1).toString();
                int h = query.value(2).toInt();
                int s = query.value(3).toInt();
                int v = query.value(4).toInt();

                Joueur *j = new Joueur(id,joueur.toStdString(),h,s,v);
                joueurs.push_back(j);

                ui->listJoueurs->addItem(joueur);
            }
        mydb.close();
    }

}

void MainWindow::loadBestScores(){
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString s = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(s);

    if(mydb.open()) {
        ui->listScores->clear();
        ui->labelScore->setText("Top scores");

        QSqlQuery query("SELECT DISTINCT piste, nomJoueur, score FROM Joueur j, Score s WHERE j.idJoueur = s.idJoueur GROUP BY piste ORDER BY score DESC");
            while (query.next()) {
                QString piste = query.value(0).toString();
                QString joueur = query.value(1).toString();
                QString score = query.value(2).toString();

                ui->listScores->addItem(piste + " : " + score + " de " + joueur);
        }
        mydb.close();
    }

}

void MainWindow::loadPisteScores(QString nomPiste){
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString s = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(s);

    if(mydb.open()) {
        ui->listScores->clear();
        ui->labelScore->setText("Top scores : " + nomPiste);

        QSqlQuery query("SELECT nomJoueur, score FROM Joueur j, Score s WHERE j.idJoueur = s.idJoueur AND piste = '" + nomPiste + "' ORDER BY score DESC");
            while (query.next()) {
                QString joueur = query.value(0).toString();
                QString score = query.value(1).toString();

                ui->listScores->addItem(joueur + " : " + score);
        }
        mydb.close();
    }

}
