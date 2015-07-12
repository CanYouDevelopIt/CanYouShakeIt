#ifndef JOUEUR_H
#define JOUEUR_H
#pragma once
#include <string>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

class Joueur
{
private:
    int xPos, yPos;
    Scalar HSVmin, HSVmax;
    std::string nomJoueur;
    int score;
public:
    Joueur();
    ~Joueur();
    Joueur(Scalar max);
    Joueur(string nomUser);

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
    int getScore();
    void setScore(int _score);

};
#endif // JOUEUR_H
