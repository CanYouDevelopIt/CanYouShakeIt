#include "joueur.h"


Joueur::Joueur(){
    setHSVmin(Scalar(0, 0, 0));
    setHSVmax(Scalar(28, 256, 149));
}

Joueur::Joueur(string nom){

    nomJoueur = nom;
    if (nomJoueur == "Jeremy"){
        setHSVmin(Scalar(0, 0, 0));
        setHSVmax(Scalar(28, 256, 149));
    }
    if (nomJoueur == "Pascal"){
        setHSVmin(Scalar(0, 0, 0));
        setHSVmax(Scalar(15, 116, 242));
    }

}

Joueur::Joueur(Scalar max){
    HSVmin = Scalar(0,0,0);
    HSVmax = max;
}

Joueur::~Joueur(){

}

int Joueur::getXPos(){
    return xPos;
}

int Joueur::getYPos(){
    return yPos;
}

void Joueur::setXPos(int x){
    xPos = x;
}

void Joueur::setYPos(int y){
    yPos = y;
}

Scalar Joueur::getHSVmin(){
    return HSVmin;
}

Scalar Joueur::getHSVmax(){
    return HSVmax;
}

void Joueur::setHSVmin(Scalar min){
    HSVmin = min;
}

void Joueur::setHSVmax(Scalar max){
    HSVmax = max;
}

int Joueur::getScore(){
    return score;
}

void Joueur::setScore(int _score){
    score += _score;
}
