#include "mouvement.h"


Mouvement::Mouvement(){
    setHSVmin(Scalar(0, 0, 0));
    setHSVmax(Scalar(28, 256, 149));
}

Mouvement::Mouvement(string nom){

    nomJoueur = nom;
    if (nomJoueur == "Jeremy"){
        setHSVmin(Scalar(0, 0, 0));
        setHSVmax(Scalar(28, 256, 149));
    }
    if (nomJoueur == "Pascal"){
        setHSVmin(Scalar(0, 0, 0));
        setHSVmax(Scalar(15, 116, 242));
    }

    //switch (nomJoueur){
    //	case "Jeremy":
    //		setHSVmin(Scalar(0, 0, 0));
    //		setHSVmax(Scalar(16, 171, 153));
    //		break;

    //}

}

Mouvement::Mouvement( Scalar max){
    HSVmin = Scalar(0,0,0);
    HSVmax = max;
}

Mouvement::~Mouvement(){

}

int Mouvement::getXPos(){
    return xPos;
}

int Mouvement::getYPos(){
    return yPos;
}

void Mouvement::setXPos(int x){
    xPos = x;
}

void Mouvement::setYPos(int y){
    yPos = y;
}

Scalar Mouvement::getHSVmin(){
    return HSVmin;
}

Scalar Mouvement::getHSVmax(){
    return HSVmax;
}

void Mouvement::setHSVmin(Scalar min){
    HSVmin = min;
}

void Mouvement::setHSVmax(Scalar max){
    HSVmax = max;
}
