#include "Mouvement.h"

Mouvement::Mouvement(){

}

Mouvement::Mouvement(string nom){

	nomJoueur = nom;
	if (nomJoueur == "Jeremy"){
		setHSVmin(Scalar(0, 0, 0));
		setHSVmax(Scalar(28, 256, 149));
	}

	//switch (nomJoueur){
	//	case "Jeremy":
	//		setHSVmin(Scalar(0, 0, 0));
	//		setHSVmax(Scalar(16, 171, 153));
	//		break;

	//}

}

Mouvement::Mouvement(Scalar min, Scalar max){
	HSVmin = min;
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
