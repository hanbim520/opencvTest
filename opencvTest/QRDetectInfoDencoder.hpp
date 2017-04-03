//
//  QRDetectInfoDencoder.hpp
//  opencvTest
//
//  Created by abc on 03/04/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#ifndef QRDetectInfoDencoder_hpp
#define QRDetectInfoDencoder_hpp

#include <stdio.h>
#include "zxing/common/Counted.h"
#include "zxing/Binarizer.h"
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/MatSource.h>
#include "zxing/LuminanceSource.h"
#include "zxing/Reader.h"   
#include "ZXing.h"
#include "zxing/MultiFormatReader.h"
#include "zxing/qrcode/QRCodeReader.h"
#include <exception>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace zxing;
using namespace zxing::qrcode;
using namespace cv;

class QRDetectInfoDencoder
{
public:
    QRDetectInfoDencoder();
    ~QRDetectInfoDencoder();
    
private:
    Point toCvPoint(Ref<ResultPoint> resultPoint) {
        return Point(resultPoint->getX(), resultPoint->getY());
    }
    
private:
    Mat grey;
    bool multi = false;
public:
    void QRDecode(Mat frame);
};


#endif /* QRDetectInfoDencoder_hpp */
