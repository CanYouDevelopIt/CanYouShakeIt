#ifndef JOUEUR_H
#define JOUEUR_H
#pragma once
#include <string>
#include <list>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <QtSql>
#include "score.h"

using namespace cv;

class Joueur
{
private:
    int xPos, yPos;
    Scalar HSVmin, HSVmax;
    int idJoueur;
    std::string nomJoueur;
    std::list<Score> mesScores;

public:
    Joueur();
    ~Joueur();
    Joueur(Scalar max);
    Joueur(string nomUser);
    Joueur(int _id, std::string _nomJoueur, int h, int s, int v);

    int getXPos();
    int getYPos();
    void setXPos(int x);
    void setYPos(int y);
    Scalar getHSVmin();
    Scalar getHSVmax();
    void setHSVmin(Scalar min);
    void setHSVmax(Scalar max);
    std::string getNomJoueur(){ return nomJoueur; }
    void setNomJoueur(std::string nom){ nomJoueur = nom;}
    std::list<Score> getMesScores();
    void addScore(Score s);
};
#endif // JOUEUR_H
