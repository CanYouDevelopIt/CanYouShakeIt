#include<opencv2/core/core.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<vector>
#include<Windows.h>
#include<MMSystem.h>

using namespace std;
using namespace cv;

int tabPosMouv[2] = { 0, 0 };
Rect rectangleContour = Rect(0, 0, 0, 0);

void rechercherMouvement(Mat thresholdImage, Mat &flux, Rect const &fleche){
	bool mouvementDetecte = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours.size()>0)mouvementDetecte = true;
	else mouvementDetecte = false;

	if (mouvementDetecte){
		vector< vector<Point> > maxContourVec;
		maxContourVec.push_back(contours.at(contours.size() - 1));
		rectangleContour = boundingRect(maxContourVec.at(0));

		int xpos = rectangleContour.x + rectangleContour.width / 2;
		int ypos = rectangleContour.y + rectangleContour.height / 2;

		tabPosMouv[0] = xpos, tabPosMouv[1] = ypos;
	}

	int x = tabPosMouv[0];
	int y = tabPosMouv[1];

	line(flux, Point(x, y), Point(x, y - 10), Scalar(0, 255, 0));
	line(flux, Point(x, y), Point(x, y + 10), Scalar(0, 255, 0));
	line(flux, Point(x, y), Point(x - 10, y), Scalar(0, 255, 0));
	line(flux, Point(x, y), Point(x + 10, y), Scalar(0, 255, 0));

	if (x >= fleche.x && x < (fleche.x + 70) && y >= fleche.y && y < (fleche.y + 70)){
		cout << "PERFECT" << endl;
	}

}

int main(){
	bool trackingMouvement = false;
	bool pause = false;
	Mat grayImage1, grayImage2;
	Mat differenceImage;
	Mat thresholdImage;

	VideoCapture capture;
	capture.open(0);

	if (!capture.isOpened()){
		cerr << "Une erreur est survenue lors de l'activation de la webcam." << endl;
		return -1;
	}

	Mat imageno = imread("Images/no.png", 0);
	Mat imagene = imread("Images/ne.png", 0);
	Mat imagese = imread("Images/se.png", 0);
	Mat imageso = imread("Images/so.png", 0);

	if (!imageno.data && !imagene.data && !imagese.data && !imageso.data)                              // Check for invalid input
	{
		cout << "Pas d'image" << std::endl;
		return -1;
	}

	cv::resize(imageno, imageno, Size(70, 70));
	cv::resize(imagene, imagene, Size(70, 70));
	cv::resize(imagese, imagese, Size(70, 70));
	cv::resize(imageso, imageso, Size(70, 70));
	Mat frame1, frame2;

	for (;;){

		capture.read(frame1);
		cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);

		capture.read(frame2);
		cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);

		absdiff(grayImage1, grayImage2, differenceImage);
		threshold(differenceImage, thresholdImage, 40, 255, THRESH_BINARY);
		threshold(thresholdImage, thresholdImage, 40, 255, THRESH_BINARY);

		Rect no = Rect(0, 0, 70, 70);
		Rect so = Rect(0, frame1.rows - 70, 70, 70);
		Rect ne = Rect(frame1.cols - 70, 0, 70, 70);
		Rect se = Rect(frame1.cols - 70, frame1.rows - 70, 70, 70);

		if (trackingMouvement){
			rechercherMouvement(thresholdImage, frame1, se);
		}

		Mat newFrame = frame1.clone();
		int cx = (newFrame.cols - 70) / 2;

		if (!imageno.empty() && !imagene.empty() && !imagese.empty() && !imageso.empty()) {

			Mat srcBGRno = Mat(imageno.size(), CV_8UC3);
			Mat srcBGRne = Mat(imagene.size(), CV_8UC3);
			Mat srcBGRso = Mat(imageso.size(), CV_8UC3);
			Mat srcBGRse = Mat(imagese.size(), CV_8UC3);

			cvtColor(imageno, srcBGRno, CV_GRAY2BGR);
			cvtColor(imagene, srcBGRne, CV_GRAY2BGR);
			cvtColor(imageso, srcBGRso, CV_GRAY2BGR);
			cvtColor(imagese, srcBGRse, CV_GRAY2BGR);

			Mat on = newFrame(no);
			Mat os = newFrame(so);
			Mat en = newFrame(ne);
			Mat es = newFrame(se);

			srcBGRno.copyTo(on);
			srcBGRso.copyTo(os);
			srcBGRne.copyTo(en);
			srcBGRse.copyTo(es);

		}

		imshow("Can You Shake It ?", newFrame);

		switch (waitKey(10)){

		case 27:
			return 0;
		case 116:
			//PlaySound(TEXT("Music/Son.wav"), NULL, SND_ASYNC);
			trackingMouvement = !trackingMouvement;
			if (trackingMouvement == false) cout << "Tracking" << endl;
			else cout << "Riennn" << endl;
			break;
		case 112:
			pause = !pause;
			if (pause == true){
				cout << "Pause !!!!!" << endl;
				while (pause == true){
					switch (waitKey()){
					case 112:

						pause = false;
						cout << "Go !!!" << endl;
						break;
					}
				}
			}


		}
	}

	return 0;
}