//
//  FaceRecognizer.hpp
//  opencvTest
//
//  Created by abc on 28/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#ifndef FaceRecognizer_hpp
#define FaceRecognizer_hpp

#include <stdio.h>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace cv::face;
using cv::face::FaceRecognizer;
using namespace std;

class FaceRecognizerWrap{
    
public:
    FaceRecognizerWrap();
    ~FaceRecognizerWrap();
    
private:
    Ptr<FaceRecognizer> EigenFacesModel;
    Ptr<FaceRecognizer> FisherFacesModel;
    Ptr<FaceRecognizer> LBPHFacesModel;
    vector<int>labels;
    vector<Mat> frames;
    
public:
    void LoadFrame(Mat frame,int label);
    void InitEigenTrain();
    void InitFisherTrain();
    void InitLBPHTrain();
    int EigenPredict(InputArray frame);
    int FisherPredict(InputArray frame);
    int LBPHPredict(InputArray frame);
    
    void EigenPredict(InputArray src, int &label, double &confidence);
    void FisherPredict(InputArray src, int &label, double &confidence);
    void LBPHPredict(InputArray src, int &label, double &confidence);
    
    Ptr<FaceRecognizer> GetEigenfacesModel(){return EigenFacesModel;}
    Ptr<FaceRecognizer> GetFisherFacesModel(){return FisherFacesModel;}
    Ptr<FaceRecognizer> GetLBPHFacesModel(){return LBPHFacesModel;}
};



#endif /* FaceRecognizer_hpp */
