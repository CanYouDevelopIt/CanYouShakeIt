#include "shakemanager.h"
#include <QDebug>

#include <iostream>
#include<vector>
#include<Windows.h>
#include<MMSystem.h>
#include <QMediaPlayer>

using namespace std;
using namespace cv;

ShakeManager::ShakeManager()
{
}

void ShakeManager::createTrackbars(){

    namedWindow("Parametrage", 0);
    char TrackbarName[50];
    sprintf(TrackbarName, "H_MAX", H_MAX);
    sprintf(TrackbarName, "S_MAX", S_MAX);
    sprintf(TrackbarName, "V_MAX", V_MAX);

    createTrackbar("H_MAX", "Parametrage", &H_MAX, H_MAX, 0);
    createTrackbar("S_MAX", "Parametrage", &S_MAX, S_MAX, 0);
    createTrackbar("V_MAX", "Parametrage", &V_MAX, V_MAX, 0);
}

void ShakeManager::afficherMouvement(vector<Joueur> &mouvements, Mat &frame){
    for (int i = 0; i < mouvements.size(); i++){
        cv::circle(frame, cv::Point(mouvements.at(i).getXPos(), mouvements.at(i).getYPos()), 10, cv::Scalar(0, 0, 255));
    }
}

void ShakeManager::morphOps(Mat &thresh){

    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
}

bool ShakeManager::rechercherMouvement(Score *scoreJoueur, Mat threshold, Mat HSV, Mat &cameraFeed, Rect const &fleche){

    vector <Joueur> mouvements;

    Mat temp;
    threshold.copyTo(temp);
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    bool mouvementTrouver = false;
    if (hierarchy.size() > 0) {

        int numObjects = hierarchy.size();

        if (numObjects<MAX_MOUVEMENT){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                if (area>MIN_OBJECT_AREA){

                    Joueur mouvement;

                    mouvement.setXPos(moment.m10 / area);
                    mouvement.setYPos(moment.m01 / area);

                    mouvements.push_back(mouvement);

                    if (mouvement.getXPos() >= fleche.x && mouvement.getXPos() < (fleche.x + 105) && mouvement.getYPos() >= fleche.y && mouvement.getYPos() < (fleche.y + 105)){
                        if(son->mediaStatus() == QMediaPlayer::PlayingState)
                            son->stop();
                        son->setMedia(QUrl("qrc:/sounds/power-up.wav"));
                        son->setVolume(5);
                        son->play();
                        scoreJoueur->addToScore(10);
                        return true;
                    }

                    mouvementTrouver = true;

                }
                else mouvementTrouver = false;

            }

            afficherMouvement(mouvements, cameraFeed);

        }
    }
    // le rectangle n'a pas été trouvé
    return false;
}

void ShakeManager::startGame(QMediaPlayer* music){

    Score *scoreJoueur = new Score();

    music->play();

    bool musicEnCours = true;

    Mat cameraFeed;
    Mat threshold;
    Mat HSV;

    VideoCapture capture;

    capture.open(0);

    if (!capture.isOpened()){
        //Une erreur est survenue lors de l'activation de la webcam
        return;
    }

    Mat imageno = imread("Images/no.png", 0);
    Mat imagene = imread("Images/ne.png", 0);
    Mat imagese = imread("Images/se.png", 0);
    Mat imageso = imread("Images/so.png", 0);

    if (!imageno.data && !imagene.data && !imagese.data && !imageso.data)
    {
        //Pas d'image
        return;
    }

    resize(imageno, imageno, Size(70, 70));
    resize(imagene, imagene, Size(70, 70));
    resize(imagese, imagese, Size(70, 70));
    resize(imageso, imageso, Size(70, 70));

    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

    boolean mouvementTrouver = false;

    int idRect = std::rand()%4;
    Rect randomRect;
    Mat srcBGR;

    while (musicEnCours){
        capture.read(cameraFeed);
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        int camRows = cameraFeed.rows;
        int camCols = cameraFeed.cols;

        Rect no = Rect(0, 0, 70, 70);
        Rect so = Rect(0, camRows - 70, 70, 70);
        Rect ne = Rect(camCols - 70, 0, 70, 70);
        Rect se = Rect(camCols - 70, camRows - 70, 70, 70);
        Rect rectPositions[] ={no,ne,so,se};

        if(mouvementTrouver){
            idRect = std::rand()%4;
        }
        randomRect = rectPositions[idRect];

        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
        inRange(HSV, joueur.getHSVmin(), joueur.getHSVmax(), threshold);
        morphOps(threshold);
        mouvementTrouver = rechercherMouvement(scoreJoueur, threshold, HSV, cameraFeed, randomRect);

        switch(idRect){
            case 0:
                srcBGR = Mat(imageno.size(), CV_8UC3);
                cvtColor(imageno, srcBGR, CV_GRAY2BGR);
                break;

            case 1:
                srcBGR = Mat(imagene.size(), CV_8UC3);
                cvtColor(imagene, srcBGR, CV_GRAY2BGR);
                break;

            case 2:
                 srcBGR = Mat(imageso.size(), CV_8UC3);
                 cvtColor(imageso, srcBGR, CV_GRAY2BGR);
                 break;

            default:
                 srcBGR = Mat(imagese.size(), CV_8UC3);
                 cvtColor(imagese, srcBGR, CV_GRAY2BGR);
                 break;
        }

        Mat ImageFeed = cameraFeed(randomRect);
        srcBGR.copyTo(ImageFeed);

        flip(cameraFeed,cameraFeed,1);
        string score = "Score : " + std::to_string(scoreJoueur->getScore());
        putText(cameraFeed, score, Point(270, 30), 1, 2, Scalar(0, 0, 255), 2);
        imshow(nomFenetre, cameraFeed);

        if(waitKey(10) == 27){
            music->stop();
            destroyWindow("Can You Shake It ? ");
            return;
        }

        if(music->state() == QMediaPlayer::StoppedState)
            musicEnCours = false;
    }

    joueur.addScore(*scoreJoueur);

}

void ShakeManager::setParameters(){

    Mat cameraFeed;
    Mat threshold;
    Mat HSV;
    createTrackbars();

    VideoCapture capture;

    capture.open(0);

    if (!capture.isOpened()){
        //Une erreur est survenue lors de l'activation de la webcam.
        return;
    }

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1200);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 700);

    while (1){
        capture.read(cameraFeed);
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
        inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
        morphOps(threshold);
        imshow("Parametrage", threshold);

        if(waitKey(10) == 27){
            int h_max = getTrackbarPos("H_MAX", "Parametrage");
            int s_max = getTrackbarPos("S_MAX", "Parametrage");
            int v_max = getTrackbarPos("V_MAX", "Parametrage");
            joueur = Joueur(Scalar(h_max,s_max,v_max));
            destroyWindow("Parametrage");
            return;
        }
    }
}


