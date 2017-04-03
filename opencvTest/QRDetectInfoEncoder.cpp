//
//  QRDetectInfo.cpp
//  opencvTest
//
//  Created by abc on 30/03/2017.
//  Copyright © 2017 abc. All rights reserved.
//

#include "QRDetectInfoEncoder.hpp"

QRDetectInfoEncoder::QRDetectInfoEncoder()
{
    
}

QRDetectInfoEncoder::~QRDetectInfoEncoder()
{
    
}

// Prints the given QR Code to the console.
void QRDetectInfoEncoder::printQr(const qrcodegen::QrCode &qr) {
    int border = 4;
    for (int y = -border; y < qr.size + border; y++) {
        for (int x = -border; x < qr.size + border; x++) {
            std::cout << (qr.getModule(x, y) == 1 ? "##" : "  ");
        }
        std::cout << std::endl;
    }
}

void QRDetectInfoEncoder::GenerateQR(std::string str)
{
    const char *text = str.c_str();  // User-supplied text
    const qrcodegen::QrCode::Ecc &errCorLvl = qrcodegen::QrCode::Ecc::HIGH;  // Error correction level
    
    // Make and print the QR Code symbol
    const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(text, errCorLvl);
    std::cout << qr.toSvgString(4) << std::endl;
    printQr(qr);
}
