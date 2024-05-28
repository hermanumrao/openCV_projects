#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <string>

using namespace std;
using namespace cv;

#include <iostream>

int main(int argc, char *argv[]) {
  string path = "resources/a1.jpeg";
  Mat img = imread(path);
  imshow("image", img);
  waitKey(0);
  return 0;
}
