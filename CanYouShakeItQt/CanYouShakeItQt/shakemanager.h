#ifndef SHAKEMANAGER_H
#define SHAKEMANAGER_H

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Mouvement.h"

class ShakeManager
{
    //initial min and max HSV filter values.
    //these will be changed using trackbars
    int H_MIN = 0;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 256;
    int V_MIN = 0;
    int V_MAX = 256;
    //default capture width and height
    const int FRAME_WIDTH = 640;
    const int FRAME_HEIGHT = 480;
    //max number of objects to be detected in frame
    const int MAX_NUM_OBJECTS = 50;
    //minimum and maximum object area
    const int MIN_OBJECT_AREA = 40 * 40;
    const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
    //names that will appear at the top of each window
    string nomFenetre = "Can You Shake It ? ";
    Mouvement mouvementCharger;
public :
    ShakeManager();
    void createTrackbars();
    void drawObject(vector<Mouvement> &mouvements, Mat &frame);
    void morphOps(Mat &thresh);
    void rechercherMouvement(Mat threshold, Mat HSV, Mat &cameraFeed);
    bool rechercherMouvement(Mouvement &m, Mat threshold, Mat HSV, Mat &cameraFeed, Rect const &fleche);
    Rect generateAMouvement(int,int);
    void startGame();
    void setParameters();
    };

#endif // SHAKEMANAGER_H
