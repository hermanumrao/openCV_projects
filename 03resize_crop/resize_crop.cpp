#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iterator>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <ostream>
#include <string>

using namespace std;
using namespace cv;

#include <iostream>

int main(int argc, char *argv[]) {
  string path = "/home/herman/workspace/openCV_projects/resources/a1.jpeg";
  Mat img = imread(path);

  if (img.empty()) {
    cout << "Could not load image at " << path << endl;
    return -1;
  } else {
    cout << "size of input image is" << img.size() << endl;
  }

  Mat imgResize1, imgResize2, imgCrop;

  resize(img, imgResize1, Size(), 0.5, 0.5);
  resize(img, imgResize2, Size(200, 200));

  Rect roi(200, 100, 300, 300); // region of interest
  imgCrop = img(roi);

  imshow("Original image", img);
  imshow("resize by ratio", imgResize1);
  imshow("resize by pixels", imgResize2);
  imshow("croping", imgCrop);
  waitKey(0);
  return 0;
}
