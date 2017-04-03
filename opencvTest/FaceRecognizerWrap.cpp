//
//  FaceRecognizer.cpp
//  opencvTest
//
//  Created by abc on 28/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#include "FaceRecognizerWrap.hpp"
#include <vector>

using cv::face::createEigenFaceRecognizer;
using cv::face::createFisherFaceRecognizer;
using cv::face::createLBPHFaceRecognizer;


FaceRecognizerWrap::FaceRecognizerWrap()
{
    EigenFacesModel = createEigenFaceRecognizer(0,1);
    FisherFacesModel = createFisherFaceRecognizer(0,1);
    LBPHFacesModel = createLBPHFaceRecognizer(1, 8, 8, 8, 80.0);
}

FaceRecognizerWrap::~FaceRecognizerWrap()
{
    
}

void FaceRecognizerWrap::LoadFrame(cv::Mat frame,int label)
{
    frames.push_back(frame);
    labels.push_back(label);
}

void FaceRecognizerWrap::InitLBPHTrain()
{
    LBPHFacesModel->train(frames, labels);
}

void FaceRecognizerWrap::InitEigenTrain()
{
    EigenFacesModel->train(frames, labels);
}

void FaceRecognizerWrap::InitFisherTrain()
{
    FisherFacesModel->train(frames, labels);
}

int FaceRecognizerWrap::EigenPredict(InputArray frame)
{
    return EigenFacesModel->predict(frame);
}

int FaceRecognizerWrap::FisherPredict(InputArray frame)
{
    return FisherFacesModel->predict(frame);
}

int FaceRecognizerWrap::LBPHPredict(InputArray frame)
{
    return LBPHFacesModel->predict(frame);
}

void FaceRecognizerWrap::EigenPredict(InputArray src, int &label, double &confidence)
{ 
    EigenFacesModel->predict(src, label, confidence);
}

void FaceRecognizerWrap::FisherPredict(InputArray src, int &label, double &confidence)
{
    FisherFacesModel->predict(src, label, confidence);
}


void FaceRecognizerWrap::LBPHPredict(InputArray src, int &label, double &confidence)
{
    LBPHFacesModel->predict(src, label, confidence);
}




