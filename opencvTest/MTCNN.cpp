
//using std::iota;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "facedetect.hpp"

using namespace std;
using namespace cv;



int main(int argc, char **argv) {
    VideoCapture capture;
    //std::cout << "Hello, world!" << std::endl;
    FaceDetector fd("/Users/abc/work/opencvTest/opencvTest/models", FaceDetector::MODEL_V1);
     Mat frame, image;
    capture.open(0);
    if( capture.isOpened() )
    {
        cout << "Video capturing has been started ..." << endl;
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;
            
            Mat frame1 = frame.clone();
           
            vector<FaceDetector::BoundingBox> res = fd.Detect(frame1, FaceDetector::BGR, FaceDetector::ORIENT_UP ,20, 0.6, 0.7, 0.7);
            cout<< "detected face NUM : " << res.size() << endl;
            for(int k = 0; k < res.size(); k++)
            {
                cv::rectangle(frame1, cv::Point(res[k].x1, res[k].y1), cv::Point(res[k].x2, res[k].y2), cv::Scalar(0, 255, 255), 2);
                //for(int i = 0; i < 5; i ++)
                //    cv::circle(frame1, cv::Point(res[k].points_x[i], res[k].points_y[i]), 2, cv::Scalar(0, 255, 255), 2);
            }
            cv::imshow("test", frame1);

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    
    
//    vector<string> imgList;
//    readFileList("/Users/abc/work/MTCNN", imgList);
//    for(int l = 0; l < imgList.size(); l ++)
//    {
//        cv::Mat testImg = cv::imread(imgList[l]);
//        
//        vector<FaceDetector::BoundingBox> res = fd.Detect(testImg, FaceDetector::BGR, FaceDetector::ORIENT_UP ,20, 0.6, 0.7, 0.7);
//        cout<< "detected face NUM : " << res.size() << endl;
//        for(int k = 0; k < res.size(); k++)
//        {
//            cv::rectangle(testImg, cv::Point(res[k].x1, res[k].y1), cv::Point(res[k].x2, res[k].y2), cv::Scalar(0, 255, 255), 2);
//            for(int i = 0; i < 5; i ++)
//                cv::circle(testImg, cv::Point(res[k].points_x[i], res[k].points_y[i]), 2, cv::Scalar(0, 255, 255), 2);
//        }
//        cv::imshow("test", testImg);
//        cv::waitKey();
//    }
    return 0;
}
