#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QListWidget>
#include <QtSql>
#include <String>
#include <list>
#include "Joueur.h"
#include "shakemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_clicked();
    void on_setParameters_clicked();

private:
    std::list<Joueur*> joueurs;
    Ui::MainWindow *ui;
    void loadPlayers();
    void loadBestScores();
    void loadPisteScores(QString nomPiste);
};

#endif // MAINWINDOW_H
