#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {

  // Blank Image
  Mat img(
      512, 512, CV_8UC3,
      Scalar(0, 0, 0)); // creates a 512x512 imge , CV_8UC3 tells that we are
                        // using a scale of 2^8 to define colors, U tells
                        // unsignes 0-255 and C3 means 3 colors (R,G,B)

  circle(img, Point(256, 256), 155, Scalar(0, 69, 255),
         FILLED); // creates a circle |  use a number instad of filled to define
                  // thickness
  rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255),
            FILLED);
  line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

  putText(img, "Herman the great", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75,
          Scalar(0, 69, 255), 2);

  imshow("Image", img);
  waitKey(0);
}
