#ifndef SCORE_H
#define SCORE_H

#include <string>

using namespace std;

class Score
{
private:
    int idScore;
    int score;
    string piste;
public:
    Score();
    Score(int _idScore, int _score, string _piste);
    int getScore();
    string getPiste();
    void addToScore(int _score);
    void setPiste(string _piste);
};

#endif // SCORE_H
