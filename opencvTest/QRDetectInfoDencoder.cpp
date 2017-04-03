//
//  QRDetectInfoDencoder.cpp
//  opencvTest
//
//  Created by abc on 03/04/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#include "QRDetectInfoDencoder.hpp"

QRDetectInfoDencoder::QRDetectInfoDencoder()
{
    
}

QRDetectInfoDencoder::~QRDetectInfoDencoder()
{
    
}

void QRDetectInfoDencoder::QRDecode(cv::Mat frame)
{
    cvtColor(frame, grey, CV_BGR2GRAY);
    try {
        // Create luminance  source
        Ref<LuminanceSource> source = MatSource::create(grey);
        
        
        // Search for QR code
        Ref<Reader> reader;
        
        if (multi) {
            reader.reset(new MultiFormatReader());
        } else {
            reader.reset(new QRCodeReader());
        }
        
        Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
        Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
        Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));
        
        // Get result point count
        int resultPointCount = result->getResultPoints()->size();
        for (int j = 0; j < resultPointCount; j++) {
            
            // Draw circle
            circle(frame, toCvPoint(result->getResultPoints()[j]), 10, Scalar( 110, 220, 0 ), 2);
            
        }
        
        // Draw boundary on image
        if (resultPointCount > 1) {
            
            for (int j = 0; j < resultPointCount; j++) {
                
                // Get start result point
                Ref<ResultPoint> previousResultPoint = (j > 0) ? result->getResultPoints()[j - 1] : result->getResultPoints()[resultPointCount - 1];
                
                // Draw line
                line(frame, toCvPoint(previousResultPoint), toCvPoint(result->getResultPoints()[j]), Scalar( 110, 220, 0 ),  2, 8 );
                
                // Update previous point
                previousResultPoint = result->getResultPoints()[j];
                
            }
            
        }
        
        if (resultPointCount > 0) {
            
            std::cout <<"qrcode result" << result->getText()->getText() <<std::endl;
            // Draw text
            putText(frame, result->getText()->getText(), toCvPoint(result->getResultPoints()[0]), FONT_HERSHEY_PLAIN, 1, Scalar( 110, 220, 0 ));
            
        }
        
    } catch (const ReaderException& e) {
        cerr << e.what() << " (ignoring1)" << endl;
    } catch (const zxing::IllegalArgumentException& e) {
        cerr << e.what() << " (ignoring2)" << endl;
    } catch (const zxing::Exception& e) {
        cerr << e.what() << " (ignoring3)" << endl;
    } catch (const std::exception& e) {
        cerr << e.what() << " (ignoring4)" << endl;
    }
    
}
