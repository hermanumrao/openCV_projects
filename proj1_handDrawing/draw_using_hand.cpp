#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

#include <iostream>

Mat img;
vector<vector<int>> newpoints;
vector<vector<int>> mycolors = {
    {123, 116, 110, 179, 205,
     245},                     // red hsv limits | hmin,smin,vmin,hmax,smax,vmax
    {30, 40, 50, 89, 97, 248}, // green hsv
    {90, 185, 30, 110, 255, 255}};            // blue hsv
vector<Scalar> myColorValues = {{0, 0, 256},  // red color
                                {0, 256, 0},  // green color
                                {256, 0, 0}}; // blue color

Point getcontours(Mat img) {
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  vector<vector<Point>> conPoly(contours.size());
  vector<Rect> boundRect(contours.size());
  Point myPoint(0, 0);

  for (int i = 0; i < contours.size(); i++) {
    int area = contourArea(contours[i]);
    cout << area;
    string objectType;
    if (area > 1000) {
      float peri = arcLength(contours[i], true);
      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

      cout << conPoly[i].size() << endl;
      boundRect[i] = boundingRect(conPoly[i]);
      myPoint.x = boundRect[i].x + boundRect[i].width / 2;
      myPoint.y = boundRect[i].y;

      // drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
      // rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0),
      // 5);
    }
  }
  return myPoint;
}

vector<vector<int>> findColor(Mat img) {
  Mat imgHSV, mask;
  cvtColor(img, imgHSV, COLOR_BGR2HSV);
  for (int i = 0; i < mycolors.size(); i++) {
    Scalar lower(mycolors[i][0], mycolors[i][1], mycolors[i][2]);
    Scalar upper(mycolors[i][3], mycolors[i][4], mycolors[i][5]);
    inRange(imgHSV, lower, upper, mask);

    Point myPoint = getcontours(mask);
    if (myPoint.x != 0) {
      newpoints.push_back({myPoint.x, myPoint.y, i});
    }
  }
  return newpoints;
}

void drawOnCanvas(vector<vector<int>> newpoints, vector<Scalar> myColorValues) {
  for (int i = 0; i < newpoints.size(); i++) {
    circle(img, Point(newpoints[i][0], newpoints[i][1]), 10,
           myColorValues[newpoints[i][2]], FILLED);
  }
}

int main(int argc, char *argv[]) {
  VideoCapture cap(0);

  while (true) {

    cap.read(img);
    newpoints = findColor(img);
    drawOnCanvas(newpoints, myColorValues);
    imshow("video", img);
    waitKey(2);
  }
  return 0;
}
