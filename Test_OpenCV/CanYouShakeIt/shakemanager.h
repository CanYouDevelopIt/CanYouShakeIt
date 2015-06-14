#ifndef SHAKEMANAGER_H
#define SHAKEMANAGER_H

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ShakeManager
{
    int tabPosMouv[2];
    cv::Rect rectangleContour;
    public:
    ShakeManager();
    void launchApplication();
    void rechercherMouvement(cv::Mat thresholdImage, cv::Mat &flux, cv::Rect const &fleche);
};

#endif // SHAKEMANAGER_H
