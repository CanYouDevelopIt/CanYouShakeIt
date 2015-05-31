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


const static int SENSITIVITY_VALUE = 40;
const static int BLUR_SIZE = 20;
int theObject[2] = { 0, 0 };
Rect objectBoundingRectangle = Rect(0, 0, 0, 0);

string intToString(int number){

	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed){
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours.size()>0)objectDetected = true;
	else objectDetected = false;

	if (objectDetected){
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size() - 1));
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
		int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;


		theObject[0] = xpos, theObject[1] = ypos;
	}
	int x = theObject[0];
	int y = theObject[1];
	circle(cameraFeed, Point(x, y), 30, Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y - 30), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y + 30), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x - 30, y), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x + 30, y), Scalar(0, 255, 0), 2);
	putText(cameraFeed, "(" + intToString(x) + "," + intToString(y) + ")", Point(x, y), 1, 1, Scalar(255, 0, 0), 2);



}

int main(){
	bool objectDetected = false;
	bool trackingEnabled = false;
	bool pause = false;
	Mat grayImage1, grayImage2;
	Mat differenceImage;
	Mat thresholdImage;

	VideoCapture capture;
	capture.open(0);

	if (!capture.isOpened()){
		cerr << "Error opening the webcam!" << endl;
		return -1;
	}
	Mat imageno = imread("Images/no.png", 0);
	Mat imagene = imread("Images/ne.png", 0);
	Mat imagese = imread("Images/se.png", 0);
	Mat imageso = imread("Images/so.png", 0);
	if (!imageno.data && !imagene.data && !imagese.data && !imageso.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
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
		threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);

		blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));

		threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);

		if (trackingEnabled){
			searchForMovement(thresholdImage, frame1);
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

			Rect no = Rect(0, 0, 70, 70);
			Rect so = Rect(0, newFrame.rows - 70, 70, 70);
			Rect ne = Rect(newFrame.cols -70, 0, 70, 70);
			Rect se = Rect(newFrame.cols - 70, newFrame.rows - 70, 70, 70);

			Mat on = newFrame(no);
			Mat os = newFrame(so);
			Mat en = newFrame(ne);
			Mat es = newFrame(se);

			srcBGRno.copyTo(on);
			srcBGRso.copyTo(os);
			srcBGRne.copyTo(en);
			srcBGRse.copyTo(es);
		}
		imshow("frame", newFrame);
		
		switch (waitKey(10)){                                  

		case 27:
			return 0;
		case 116: 
			PlaySound(TEXT("Music/Son.wav"), NULL, SND_ASYNC);
			trackingEnabled = !trackingEnabled;
			if (trackingEnabled == false) cout << "Tracking" << endl;
			else cout << "Riennn" << endl;
			break;
		case 112:
			pause = !pause;
			if (pause == true){
				cout << "Code paused, press 'p' again to resume" << endl;
				while (pause == true){
					
					switch (waitKey()){
						
					case 112:
						
						pause = false;
						cout << "Code resumed." << endl;
						break;
					}
				}
			}


		}
	}

	return 0;
}