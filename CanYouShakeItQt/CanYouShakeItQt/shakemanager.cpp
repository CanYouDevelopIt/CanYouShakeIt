#include "shakemanager.h"
#include <QDebug>

#include <iostream>
#include<vector>
#include<Windows.h>
#include<MMSystem.h>

using namespace std;
using namespace cv;

ShakeManager::ShakeManager()
{
}

void ShakeManager::createTrackbars(){
    //create window for trackbars

    namedWindow("Parametrage", 0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf(TrackbarName, "H_MAX", H_MAX);
    sprintf(TrackbarName, "S_MAX", S_MAX);
    sprintf(TrackbarName, "V_MAX", V_MAX);

    createTrackbar("H_MAX", "Parametrage", &H_MAX, H_MAX, 0);
    createTrackbar("S_MAX", "Parametrage", &S_MAX, S_MAX, 0);
    createTrackbar("V_MAX", "Parametrage", &V_MAX, V_MAX, 0);
}

void ShakeManager::drawObject(vector<Mouvement> &mouvements, Mat &frame){
    for (int i = 0; i < mouvements.size(); i++){
        cv::circle(frame, cv::Point(mouvements.at(i).getXPos(), mouvements.at(i).getYPos()), 10, cv::Scalar(0, 0, 255));
    }
}

void ShakeManager::morphOps(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle

    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);


    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
}
void ShakeManager::rechercherMouvement(Mat threshold, Mat HSV, Mat &cameraFeed){

    vector <Mouvement> mouvements;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if (numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if (area>MIN_OBJECT_AREA){

                    Mouvement m;

                    m.setXPos(moment.m10 / area);
                    m.setYPos(moment.m01 / area);

                    mouvements.push_back(m);

                    objectFound = true;

                }else objectFound = false;

            }
            //let user know you found an object
            if (objectFound == true){
                //draw object location on screen
                drawObject(mouvements, cameraFeed);
            }

        }
        else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }
}

bool ShakeManager::rechercherMouvement(Mouvement &m, Mat threshold, Mat HSV, Mat &cameraFeed, Rect const &fleche){

    vector <Mouvement> mouvements;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if (numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if (area>MIN_OBJECT_AREA){

                    Mouvement m;

                    m.setXPos(moment.m10 / area);
                    m.setYPos(moment.m01 / area);

                    mouvements.push_back(m);

                    if (m.getXPos() >= fleche.x && m.getXPos() < (fleche.x + 105) && m.getYPos() >= fleche.y && m.getYPos() < (fleche.y + 105)){
                        std::cout << "PERFECT" << std::endl;
                        // le rectangle a été trouvé
                        return true;
                    }

                    objectFound = true;

                }
                else objectFound = false;

            }
            //let user know you found an object
            if (objectFound == true){
                //draw object location on screen
                drawObject(mouvements, cameraFeed);
            }

        }
        else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }
    // le rectangle n'a pas été trouvé
    return false;
}

void ShakeManager::startGame(){

    bool pause = false;

    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    Mat threshold;
    Mat HSV;

    VideoCapture capture;

    capture.open(0);

    if (!capture.isOpened()){
        std::cerr << "Une erreur est survenue lors de l'activation de la webcam." << std::endl;
        return;
    }

    Mat imageno = imread("Images/no.png", 0);
    Mat imagene = imread("Images/ne.png", 0);
    Mat imagese = imread("Images/se.png", 0);
    Mat imageso = imread("Images/so.png", 0);

    if (!imageno.data && !imagene.data && !imagese.data && !imageso.data)                              // Check for invalid input
    {
        std::cout << "Pas d'image" << std::endl;
        return;
    }

    resize(imageno, imageno, Size(70, 70));
    resize(imagene, imagene, Size(70, 70));
    resize(imagese, imagese, Size(70, 70));
    resize(imageso, imageso, Size(70, 70));

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //start an infinite loop where webcam feed is copied to cameraFeed matrix

    boolean mouvementTrouver = false;
    // le 1er rectangle que l'utilisateur doit atteindre
    Rect randomRect = Rect(0, 0, 70, 70);
    while (1){
        //store image to matrix
        capture.read(cameraFeed);
        //convert frame from BGR to HSV colorspace
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        int camRows = cameraFeed.rows;
        int camCols = cameraFeed.cols;

        Rect no = Rect(0, 0, 70, 70);
        Rect so = Rect(0, camRows - 70, 70, 70);
        Rect ne = Rect(camCols - 70, 0, 70, 70);
        Rect se = Rect(camCols - 70, camRows - 70, 70, 70);

        if(mouvementTrouver){
        // génére un autre rectangle à trouver
        randomRect = generateAMouvement(camRows,camCols);
        }
        //mouvementCharger = Mouvement("Pascal");
        //mouvementCharger(Scalar(15, 116, 242));
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
        inRange(HSV, mouvementCharger.getHSVmin(), mouvementCharger.getHSVmax(), threshold);
        morphOps(threshold);
        mouvementTrouver = rechercherMouvement(mouvementCharger, threshold, HSV, cameraFeed, randomRect);


        Mat srcBGRno = Mat(imageno.size(), CV_8UC3);
        Mat srcBGRne = Mat(imagene.size(), CV_8UC3);
        Mat srcBGRso = Mat(imageso.size(), CV_8UC3);
        Mat srcBGRse = Mat(imagese.size(), CV_8UC3);

        cvtColor(imageno, srcBGRno, CV_GRAY2BGR);
        cvtColor(imagene, srcBGRne, CV_GRAY2BGR);
        cvtColor(imageso, srcBGRso, CV_GRAY2BGR);
        cvtColor(imagese, srcBGRse, CV_GRAY2BGR);

        Mat on = cameraFeed(no);
        Mat os = cameraFeed(so);
        Mat en = cameraFeed(ne);
        Mat es = cameraFeed(se);

        srcBGRno.copyTo(on);
        srcBGRso.copyTo(os);
        srcBGRne.copyTo(en);
        srcBGRse.copyTo(es);

        imshow(nomFenetre, cameraFeed);

        switch (waitKey(10)){

        case 27:
            return;
        case 112:
            pause = !pause;
            if (pause == true){
                std::cout << "Pause !!!!!" << std::endl;
                while (pause == true){
                    switch (waitKey()){
                    case 112:

                        pause = false;
                        std::cout << "Go !!!" << std::endl;
                        break;
                    }
                }
            }
        }

    }


}



Rect ShakeManager::generateAMouvement(int camRows,int camCols){

    Rect no = Rect(0, 0, 70, 70);
    Rect so = Rect(0, camRows - 70, 70, 70);
    Rect ne = Rect(camCols - 70, 0, 70, 70);
    Rect se = Rect(camCols - 70, camRows - 70, 70, 70);
    Rect rectPositions[] ={no,so,ne,se};
    int randomNumber = std::rand()%4;
    std::cout << " Random Number = " << randomNumber << std::endl;
    return rectPositions[randomNumber];
}

void ShakeManager::setParameters(){

    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    Mat threshold;
    Mat HSV;
    createTrackbars();

    VideoCapture capture;

    capture.open(0);

    if (!capture.isOpened()){
        std::cerr << "Une erreur est survenue lors de l'activation de la webcam." << std::endl;
        return;
    }

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //start an infinite loop where webcam feed is copied to cameraFeed matrix

    while (1){
        //store image to matrix
        capture.read(cameraFeed);
        //convert frame from BGR to HSV colorspace
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        //if in calibration mode, we track objects based on the HSV slider values.
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
        inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
        morphOps(threshold);
        imshow("Parametrage", threshold);
        rechercherMouvement(threshold, HSV, cameraFeed);
        if(waitKey(10) == 27){
            int h_max = getTrackbarPos("H_MAX", "Parametrage");
            int s_max = getTrackbarPos("S_MAX", "Parametrage");
            int v_max = getTrackbarPos("V_MAX", "Parametrage");
            mouvementCharger = Mouvement(Scalar(h_max,s_max,v_max));
            return;
        }
    }
}


