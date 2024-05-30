#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp,
    imgCrop;
vector<Point> initialPoints, docPoints;
float w = 420, h = 596;

Mat preprocess(Mat img) {
  cvtColor(img, imgGray, COLOR_BGR2GRAY);
  GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
  Canny(imgBlur, imgCanny, 25, 75);
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  dilate(imgCanny, imgDil, kernel);

  return img;
}

vector<Point> getcontours(Mat img) {
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  vector<vector<Point>> conPoly(contours.size());
  vector<Rect> boundRect(contours.size());

  for (int i = 0; i < contours.size(); i++) {
    int area = contourArea(contours[i]);
    cout << area << endl;
    string objectType;
    if (area > 1000) {
      float peri = arcLength(contours[i], true);
      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
      cout << conPoly[i].size() << endl;
      boundRect[i] = boundingRect(conPoly[i]);

      int objCor = (int)conPoly[i].size();

      if (objCor == 3)
        objectType = "Triangle";
      else if (objCor == 4) {
        float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
        cout << aspRatio << endl;
        if (aspRatio > 0.95 && aspRatio < 1.05)
          objectType = "square";
        else
          objectType = "rectangle";
      } else if (objCor > 4)
        objectType = "circle";

      drawContours(img, conPoly, i, Scalar(0, 0, 0), 5);
      rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 255),
                5);
      putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5},
              FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 69), 2);
    }
  }
}

int main(int argc, char *argv[]) {
  string path = "/home/herman/workspace/openCV_projects/resources/pap2.jpeg";
  imgOriginal = imread(path);

  imgThre = preprocess(imgOriginal);

  return 0;
}
