#include "piste.h"

Piste::Piste()
{
}


Piste::Piste(string _cheminMusic, string _titre){
    cheminMusic = _cheminMusic;
    titre = _titre;
}

void Piste::initListMouvement(){
}

string Piste::getCheminMusic(){
    return cheminMusic;
}
string Piste::getTitre(){
    return titre;
}
list<cv::Rect> Piste::getListMouvement(){
    return listMouvement;
}
int Piste::getScore(){
    return score;
}
void Piste::setScore(int _score){
    score = _score;
}

Piste::~Piste()
{
}
