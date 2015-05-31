#pragma once
#include <string>
#include <list>
#include<opencv2/core/core.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Piste
{
	string cheminMusic;
	string titre;
	list<Rect> listMouvement;
	int score;
public:
	Piste();
	Piste(string _cheminMusic, string _titre);
	void initListMouvement();
	string getCheminMusic();
	string getTitre();
	list<Rect> getListMouvement();
	int getScore();
	void setScore(int _score);
	~Piste();
};

