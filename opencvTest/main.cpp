#include <iostream>
#include "DetectFaceInfo.hpp"
#include "QRDetectInfoEncoder.hpp"

using namespace std;


int main( int argc, const char** argv )
{
    
    QRDetectInfoEncoder qRDetectInfo;
    qRDetectInfo.GenerateQR("www.baidunnnn.com");
    
    DetectFaceInfo detectFaceInfo;
    detectFaceInfo.StartCaptureFace();
    
    
    
    return 0;
}

