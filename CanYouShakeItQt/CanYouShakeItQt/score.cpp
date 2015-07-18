#include "score.h"

Score::Score()
{

}

Score::Score(int _idScore, int _score, string _piste){
    idScore = _idScore;
    score = _score;
    piste = _piste;
}

int Score::getScore(){
    return score;
}

string Score::getPiste(){
    return piste;
}

void Score::setScore(int _score){
    score = _score;
}

void Score::setPiste(string _piste){
    piste = _piste;
}
