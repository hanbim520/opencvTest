//
//  QRDetectInfo.hpp
//  opencvTest
//
//  Created by abc on 30/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#ifndef QRDetectInfoEncoder_hpp
#define QRDetectInfoEncoder_hpp

#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "QrCode.hpp"


class QRDetectInfoEncoder
{
public:
    QRDetectInfoEncoder();
    ~QRDetectInfoEncoder();
    
public:
    static void printQr(const qrcodegen::QrCode &qr);
    static void GenerateQR(std::string str);
};


#endif /* QRDetectInfoEncoder_hpp */
