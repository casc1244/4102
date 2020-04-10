#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat Matgray;
	cv::Mat Mat_binary;
	cv::Mat Mat_canny;
	cv::Mat srcImage = imread("D:\\360downloads\\9.png");

	cvtColor(srcImage, Matgray, COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
	cv::Mat elementRect;
	elementRect = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	cv::morphologyEx(Matgray, Matgray, cv::MORPH_CLOSE, elementRect);
    // binary
	cv::threshold(Matgray, Mat_binary, 125, 255.0, cv::THRESH_BINARY);
	// detect edge
	cv::Canny(Mat_binary, Mat_canny, 50, 125, 3);
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(Mat_canny, lines, 1, CV_PI / 180, 100);

	cv::Mat lineMat;
	cv::HoughLines(Mat_canny, lineMat, 1, CV_PI / 180, 100);
	//float r = lines[0][0];
	//float t = lines[0][1];

	// draw line
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(srcImage, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}

	cv::imshow("canny", Mat_canny);
	cv::imshow("mat", srcImage);
	cv::waitKey(0);

	return 0;
}