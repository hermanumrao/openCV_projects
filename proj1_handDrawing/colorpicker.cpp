// #include <iostream>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/imgproc.hpp>
//
// using namespace cv;
// using namespace std;
//
// int main() {
//   VideoCapture cap(2);
//   Mat img;
//   Mat imgHSV, mask;
//   int hmin = 0, smin = 0, vmin = 0;
//   int hmax = 4, smax = 150, vmax = 228;
//
//   namedWindow("Trackbars", (200));
//   createTrackbar("Hue Min", "Trackbars", &hmin, 179);
//   createTrackbar("Hue Max", "Trackbars", &hmax, 179);
//   createTrackbar("Sat Min", "Trackbars", &smin, 255);
//   createTrackbar("Sat Max", "Trackbars", &smax, 255);
//   createTrackbar("Val Min", "Trackbars", &vmin, 255);
//   createTrackbar("Val Max", "Trackbars", &vmax, 255);
//
//   while (true) {
//     cap.read(img);
//     cvtColor(img, imgHSV, COLOR_BGR2HSV);
//
//     // while (true) {
//
//     Scalar lower(hmin, smin, vmin);
//     Scalar upper(hmax, smax, vmax);
//     inRange(imgHSV, lower, upper, mask);
//
//     resize(mask, mask, Size(480, 270));
//     imshow("Image Mask", mask);
//     waitKey(3);
//     // }
//   }
//   imshow("image", img);
//   waitKey(0);
// }

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
  VideoCapture cap(2);
  Mat img;
  Mat imgHSV, mask;
  int hmin = 0, smin = 0, vmin = 0;
  int hmax = 4, smax = 150, vmax = 228;

  // Create a named window with a specific size for the trackbars
  namedWindow("Trackbars", WINDOW_NORMAL);
  resizeWindow("Trackbars", 600, 400); // Adjust size as needed

  createTrackbar("Hue Min", "Trackbars", &hmin, 179);
  createTrackbar("Hue Max", "Trackbars", &hmax, 179);
  createTrackbar("Sat Min", "Trackbars", &smin, 255);
  createTrackbar("Sat Max", "Trackbars", &smax, 255);
  createTrackbar("Val Min", "Trackbars", &vmin, 255);
  createTrackbar("Val Max", "Trackbars", &vmax, 255);

  while (true) {
    cap.read(img);
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    resize(mask, mask, Size(480, 270));
    imshow("Image Mask", mask);
    if (waitKey(3) >= 0)
      break;
  }

  imshow("image", img);
  waitKey(0);
  return 0;
}
