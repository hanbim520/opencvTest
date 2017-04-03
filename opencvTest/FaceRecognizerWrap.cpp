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
    EigenfacesModel = createEigenFaceRecognizer(0,1);
    FisherfacesModel = createFisherFaceRecognizer(0,1);
    LBPHModel = createLBPHFaceRecognizer(1, 8, 8, 8, 80.0);
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
    LBPHModel->train(frames, labels);
}

void FaceRecognizerWrap::InitEigenTrain()
{
    EigenfacesModel->train(frames, labels);
}

void FaceRecognizerWrap::InitFisherTrain()
{
    FisherfacesModel->train(frames, labels);
}

int FaceRecognizerWrap::EigenPredict(InputArray frame)
{
    return EigenfacesModel->predict(frame);
}

int FaceRecognizerWrap::FisherPredict(InputArray frame)
{
    return FisherfacesModel->predict(frame);
}

int FaceRecognizerWrap::LBPHPredict(InputArray frame)
{
    return LBPHModel->predict(frame);
}

void FaceRecognizerWrap::EigenPredict(InputArray src, int &label, double &confidence)
{ 
    EigenfacesModel->predict(src, label, confidence);
}

void FaceRecognizerWrap::FisherPredict(InputArray src, int &label, double &confidence)
{
    FisherfacesModel->predict(src, label, confidence);
}


void FaceRecognizerWrap::LBPHPredict(InputArray src, int &label, double &confidence)
{
    LBPHModel->predict(src, label, confidence);
}




