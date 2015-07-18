#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <String>
#include <list>
#include "Joueur.h"

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
    QList<Joueur> joueurs;
    Ui::MainWindow *ui;
    void loadPlayers();
};

#endif // MAINWINDOW_H
