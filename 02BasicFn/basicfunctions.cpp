#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <string>

using namespace std;
using namespace cv;

#include <iostream>

int main(int argc, char *argv[]) {
  string path = "/home/herman/workspace/openCV_projects/resources/a2.jpg";
  Mat img = imread(path);
  Mat imgGray, imgBlur, imgCanny, imgDila, imgErode;

  cvtColor(img, imgGray, COLOR_BGR2GRAY);
  GaussianBlur(img, imgBlur, Size(7, 7), 5, 6);
  Canny(imgBlur, imgCanny, 25, 74);

  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  dilate(img, imgDila, kernel);
  erode(img, imgErode, kernel);

  imshow("Original image", img);
  imshow("Grayscale image", imgGray);
  imshow("blurred image", imgBlur);
  imshow("outlined image", imgCanny);
  imshow("dialation image", imgDila);
  imshow("eroded image", imgErode);

  waitKey(0);
  return 0;
}
