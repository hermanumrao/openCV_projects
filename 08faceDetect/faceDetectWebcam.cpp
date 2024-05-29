#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

#include <iostream>

int main(int argc, char *argv[]) {
  VideoCapture cap(0);
  Mat img;

  CascadeClassifier faceCascade;
  faceCascade.load("/home/herman/workspace/openCV_projects/resources/"
                   "haarcascade_frontalface_default.xml");

  if (faceCascade.empty()) {
    cout << "xml file did not load" << endl;
    exit(0);
  }
  vector<Rect> faces;

  while (true) {
    cap.read(img);

    faceCascade.detectMultiScale(img, faces, 1.05, 10);

    for (int i = 0; i < faces.size(); i++) {
      rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 2);
    }

    imshow("WebCam video", img);
    waitKey(10);
  }

  imshow("image", img);
  waitKey(0);

  return 0;
}
