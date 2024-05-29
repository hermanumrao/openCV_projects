#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {

  string path = "/home/herman/workspace/openCV_projects/resources/a1.jpeg";
  Mat img = imread(path);
  Mat imgHSV, mask;
  int hmin = 35, smin = 100, vmin = 153;
  int hmax = 54, smax = 150, vmax = 228;

  cvtColor(img, imgHSV, COLOR_BGR2HSV);

  namedWindow("Trackbars", (200));
  createTrackbar("Hue Min", "Trackbars", &hmin, 179);
  createTrackbar("Hue Max", "Trackbars", &hmax, 179);
  createTrackbar("Sat Min", "Trackbars", &smin, 255);
  createTrackbar("Sat Max", "Trackbars", &smax, 255);
  createTrackbar("Val Min", "Trackbars", &vmin, 255);
  createTrackbar("Val Max", "Trackbars", &vmax, 255);

  while (true) {

    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    imshow("Image", img);
    imshow("Image HSV", imgHSV);
    imshow("Image Mask", mask);
    waitKey(1);
  }
}
