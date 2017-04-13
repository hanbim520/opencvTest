////
////  mainc.cpp
////  opencvTest
////
////  Created by abc on 10/04/2017.
////  Copyright © 2017 abc. All rights reserved.
////
//
//#include "mainc.hpp"
//#include <opencv2/opencv.hpp>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//using namespace cv;
//using namespace std;
//
////-----------------------------------°æmain( )∫Ø ˝°ø--------------------------------------------
//
////		√Ë ˆ£∫øÿ÷∆Ã®”¶”√≥Ã–Úµƒ»Îø⁄∫Ø ˝£¨Œ“√«µƒ≥Ã–Ú¥”’‚¿Ôø™ º
////-------------------------------------------------------------------------------------------------
//int main(int argc, char** argv)
//{
//    // °æ1°ø‘ÿ»Î‘≠ ºÕº£¨«“±ÿ–Î“‘∂˛÷µÕºƒ£ Ω‘ÿ»Î
//    Mat srcImage = imread("/Users/abc/work/opencvTest/image/1.jpg", 0);
//    imshow("‘≠ ºÕº", srcImage);
//    
//    //°æ2°ø≥ı ºªØΩ·π˚Õº
//    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
//    
//    //°æ3°øsrcImage»°¥Û”⁄„–÷µ119µƒƒ«≤ø∑÷
//    srcImage = srcImage > 119;
//    imshow("»°„–÷µ∫Ûµƒ‘≠ ºÕº", srcImage);
//    
//    //°æ4°ø∂®“Â¬÷¿™∫Õ≤„¥ŒΩ·ππ
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    
//    //°æ5°ø≤È’“¬÷¿™
//    //¥Àæ‰¥˙¬ÎµƒOpenCV2∞ÊŒ™£∫
//    //findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
//    //¥Àæ‰¥˙¬ÎµƒOpenCV3∞ÊŒ™£∫
//    findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//    
//    // °æ6°ø±È¿˙À˘”–∂•≤„µƒ¬÷¿™£¨ “‘ÀÊª˙—’…´ªÊ÷∆≥ˆ√ø∏ˆ¡¨Ω”◊Èº˛—’…´
//    int index = 0;
//    for (; index >= 0; index = hierarchy[index][0])
//    {
//        Scalar color(rand() & 255, rand() & 255, rand() & 255);
//        //¥Àæ‰¥˙¬ÎµƒOpenCV2∞ÊŒ™£∫
//        //drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
//        //¥Àæ‰¥˙¬ÎµƒOpenCV3∞ÊŒ™£∫
//        drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
//    }
//    
//    //°æ7°øœ‘ æ◊Ó∫Ûµƒ¬÷¿™Õº
//    imshow("¬÷¿™Õº", dstImage);
//    
//    waitKey(0);
//    
//}
