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

  vector<Point> biggest;
  int maxArea = 0;

  for (int i = 0; i < contours.size(); i++) {
    int area = contourArea(contours[i]);
    // cout << area << endl;
    string objectType;
    if (area > 1000) {
      float peri = arcLength(contours[i], true);
      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
      // cout << conPoly[i].size() << endl;

      if (area > maxArea && conPoly[i].size() == 4) {
        biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
        maxArea = area;
      }
    }
  }
  return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {
  for (int i = 0; i < 4; i++) {
    circle(imgOriginal, points[i], 10, color, FILLED);
    putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color,
            4);
  }
}

vector<Point> reorder(vector<Point> points) {
  vector<Point> newPoints;
  vector<int> sumPoints, subPoints;

  for (int i = 0; i < 4; i++) {
    sumPoints.push_back(points[i].x + points[i].y);
    subPoints.push_back(points[i].x - points[i].y);
  }

  newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) -
                             sumPoints.begin()]); // 0
  newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) -
                             subPoints.begin()]); // 1
  newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) -
                             subPoints.begin()]); // 2
  newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) -
                             sumPoints.begin()]); // 3

  return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {
  Point2f src[4] = {points[0], points[1], points[2], points[3]};
  Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

  Mat matrix = getPerspectiveTransform(src, dst);
  warpPerspective(img, imgWarp, matrix, Point(w, h));
  return imgWarp;
}

int main(int argc, char *argv[]) {
  string path = "/home/herman/workspace/openCV_projects/resources/pap1.jpeg";
  imgOriginal = imread(path);

  imgThre = preprocess(imgOriginal); // preprocessing         Step1

  initialPoints = getcontours(imgThre); // Get contours          Step2
  docPoints = reorder(initialPoints);   // reordering points to get it in order

  imgWarp = getWarp(imgOriginal, docPoints, w, h); // wrapping the image Step3

  int cropVal = 5; // cropping              Step4
  Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
  imgCrop = imgWarp(roi);

  imshow("document", imgOriginal);
  imshow("scanned document", imgCrop);
  waitKey(0);

  return 0;
}
