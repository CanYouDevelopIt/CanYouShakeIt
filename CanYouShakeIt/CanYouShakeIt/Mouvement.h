#pragma once
#include <string>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

class Mouvement
{
private:
	int xPos, yPos;
	Scalar HSVmin, HSVmax;
	std::string nomJoueur;

public:
	Mouvement();
	~Mouvement();
	Mouvement(Scalar min, Scalar max);
	Mouvement(string nomUser);

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

};