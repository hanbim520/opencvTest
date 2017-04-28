///*
// * EEL6562 Project
// * Real Time Object Recognition using SURF
// *
// *  Created on: Nov 15, 2013
// *      Author: Frank
// */
//
////Include statements
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include <opencv2/xfeatures2d.hpp>
////#include "opencv2/nonfree/nonfree.hpp"
//
////Name spaces used
//using namespace cv;
//using namespace std;
//using namespace xfeatures2d;
//
//int main()
//{
//    cv::Mat image;
//    image = cv::imread("/Users/abc/work/opencvTest/image/1.jpg");
//    
//    cv::Mat imageGray;
//    cv::cvtColor(image, imageGray, CV_BGR2GRAY);
//    
//    cv::Ptr<Feature2D>f2d = cv::xfeatures2d::SIFT::create();
//    std::vector<KeyPoint> keypoints;
//    f2d->detect(imageGray, keypoints);
//    //std::cout << "Success" << std::endl;
//    drawKeypoints(image, keypoints, image, cv::Scalar(0, 255, 0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//    cv::imshow("SIFT", image);
//    cv::waitKey(0);    return 0;
//}
