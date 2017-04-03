//
//  DetectFaceInfo.hpp
//  opencvTest
//
//  Created by abc on 28/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#ifndef DetectFaceInfo_hpp
#define DetectFaceInfo_hpp

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#include <stdio.h>

class DetectFaceInfo
{
public:
    DetectFaceInfo();
    ~DetectFaceInfo();
    
private:
    string faceCascadeName;
    string eyeCascadeName;
    string mouthCascadeName;
    string noseCascadeName;
    
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    bool tryflip;
    CascadeClassifier faceCascade;
    CascadeClassifier eyesCascade;
    CascadeClassifier mouthCascade;
    CascadeClassifier noseCascade;
    
    double scale;
    vector<Rect_<int>> facesVec;
    vector<Rect_<int>> eyesVec;
    vector<Rect_<int>> noseVec;
        
private:
    void detectFaces(Mat frame);
    void detectEyes(Mat frame,Rect rect,Mat smallerImg,Scalar color);
    void detectNose(Mat frame ,Rect rect,Mat smallerImg,Scalar color);
    
public:
    void StartCaptureFace();
    void StopCaptureFace();
};


#endif /* DetectFaceInfo_hpp */
