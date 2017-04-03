//
//  DetectFaceInfo.cpp
//  opencvTest
//
//  Created by abc on 28/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "DetectFaceInfo.hpp"
#include "QRDetectInfoDencoder.hpp"

using namespace std;
const static Scalar colors[] =
{
    Scalar(255,0,0),
    Scalar(255,128,0),
    Scalar(255,255,0),
    Scalar(0,255,0),
    Scalar(0,128,255),
    Scalar(0,255,255),
    Scalar(0,0,255),
    Scalar(255,0,255)
};


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator =';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message ="No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty()&&!classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

DetectFaceInfo::DetectFaceInfo()
{
    faceCascadeName = "/Users/abc/Desktop/opencvTest/haarcascades/haarcascade_frontalface_alt.xml";
    eyeCascadeName = "/Users/abc/Desktop/opencvTest/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    mouthCascadeName = "/Users/abc/Desktop/opencvTest/haarcascades/haarcascade_mcs_mouth.xml";
    noseCascadeName = "/Users/abc/Desktop/opencvTest/haarcascades/haarcascade_mcs_nose.xml";
    
    scale = 1.3;
    
    if( !faceCascade.load( faceCascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        exit(-1);
    }
    
    if ( !eyesCascade.load( eyeCascadeName ) )
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;

    if( !mouthCascade.load( mouthCascadeName ) )
    {
        cerr << "ERROR: Could not load classifier mouthCascadeName" << endl;
    }
    
    if(!noseCascade.load(noseCascadeName))
         cerr << "ERROR: Could not load classifier noseCascadeName" << endl;
}

DetectFaceInfo::~DetectFaceInfo()
{
    
}

void DetectFaceInfo::StartCaptureFace()
{
    QRDetectInfoDencoder dencoder ;
    capture.open(0);
    if( capture.isOpened() )
    {
        cout << "Video capturing has been started ..." << endl;
        
        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;
            
            Mat frame1 = frame.clone();
            detectFaces( frame1);
            Mat frame2 = frame.clone();
            dencoder.QRDecode(frame2);
            
            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

}

void DetectFaceInfo::StopCaptureFace()
{
    capture.release();
}

void DetectFaceInfo::detectFaces(Mat frame)
{
    
    Mat gray, smallImg;
    
    cvtColor( frame, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );
    
    double t = (double)getTickCount();
    
    faceCascade.detectMultiScale( smallImg, facesVec,
                             1.1, 2, 0
                             //|CASCADE_FIND_BIGGEST_OBJECT
                             //|CASCADE_DO_ROUGH_SEARCH
                             |CASCADE_SCALE_IMAGE,
                             Size(30, 30) );
    t = (double)getTickCount() - t;
  //  printf( "detection time = %g ms\n", t*1000/getTickFrequency());
    
    for ( size_t i = 0; i < facesVec.size(); i++ )
    {
        Rect r = facesVec[i];
                vector<Rect> nestedObjects;
        vector<Rect> mouthObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;
        
        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5)*scale);
            center.y = cvRound((r.y + r.height*0.5)*scale);
            radius = cvRound((r.width + r.height)*0.25*scale);
            circle( frame, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( frame, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                      cvPoint(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                      color, 3, 8, 0);
        
        detectEyes(frame,r,smallImg,color);
        detectNose(frame, r, smallImg, color);
    }
    imshow( "result", frame );
}

void DetectFaceInfo::detectNose(cv::Mat frame, Rect rect, cv::Mat smallerImg, Scalar color)
{
    if( noseCascade.empty() )
        return;
    Mat smallImgROI;
    Point center;
    int radius;
    
    smallImgROI = smallerImg( rect );
    noseCascade.detectMultiScale( smallImgROI, noseVec,
                                 1.1, 2, 0
                                 //|CASCADE_FIND_BIGGEST_OBJECT
                                 //|CASCADE_DO_ROUGH_SEARCH
                                 //|CASCADE_DO_CANNY_PRUNING
                                 |CASCADE_SCALE_IMAGE,
                                 Size(30, 30) );
    for ( size_t j = 0; j < noseVec.size(); j++ )
    {
        Rect nr = noseVec[j];
        center.x = cvRound((rect.x + nr.x + nr.width*0.5)*scale);
        center.y = cvRound((rect.y + nr.y + nr.height*0.5)*scale);
        radius = cvRound((nr.width + nr.height)*0.25*scale);
        circle( frame, center, radius, color, 3, 8, 0 );
    }
}

void DetectFaceInfo::detectEyes(Mat frame,Rect rect,Mat smallerImg,Scalar color)
{
    
    if( eyesCascade.empty() )
        return;
    Mat smallImgROI;
    Point center;
    int radius;

    smallImgROI = smallerImg( rect );
    eyesCascade.detectMultiScale( smallImgROI, eyesVec,
                                       1.1, 2, 0
                                       //|CASCADE_FIND_BIGGEST_OBJECT
                                       //|CASCADE_DO_ROUGH_SEARCH
                                       //|CASCADE_DO_CANNY_PRUNING
                                       |CASCADE_SCALE_IMAGE,
                                       Size(30, 30) );
        for ( size_t j = 0; j < eyesVec.size(); j++ )
        {
            Rect nr = eyesVec[j];
            center.x = cvRound((rect.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((rect.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( frame, center, radius, color, 3, 8, 0 );
        }
        
    
    

}
