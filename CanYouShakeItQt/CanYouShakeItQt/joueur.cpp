#include "joueur.h"

Joueur::Joueur(){
    setHSVmin(Scalar(0, 0, 0));
    setHSVmax(Scalar(28, 256, 149));
}

Joueur::Joueur(int _id, std::string _nomJoueur, int h, int s, int v){
    idJoueur = _id;
    nomJoueur = _nomJoueur;
    setHSVmin(Scalar(0, 0, 0));
    setHSVmax(Scalar(h, s, v));
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

std::list<Score> Joueur::getMesScores(){
    return mesScores;
}

void Joueur::addScore(Score s){
    mesScores.push_back(s);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString sDatabase = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(sDatabase);

    QString nomPiste = QString::fromStdString(s.getPiste());
    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "INSERT INTO SCORE(score, piste, idJoueur) VALUES(" << s.getScore() << ",'" << nomPiste << "'," << idJoueur << ")";

    if(mydb.open()){
        QSqlQuery query(queryString);
    }
}

void Joueur::saveJoueur(int h,int s, int v){

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    QString sDatabase = QUrl("../bdd/cysi.db").toString();
    mydb.setDatabaseName(sDatabase);

    QString newName = QString::fromStdString(nomJoueur);
    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "INSERT INTO JOUEUR(nomJoueur, h, s, v) VALUES('" << newName << "'," << h << "," << s << "," << v << ")";
    std::cout<< " Query ==>" << queryString.toStdString()<<endl;

    if(mydb.open()){
        std::cout<<"Cool"<<std::endl;
        QSqlQuery query(queryString);
    }else{
        std::cout<<"Error"<<std::endl;
    }
}


