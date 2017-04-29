
//using std::iota;
#include "facedetect.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "FaceRecognizerWrap.hpp"

using namespace std;
using namespace cv;

vector<string> imageLists;

std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}

void loadImages()
{
    ifstream in("/Users/abc/work/opencvTest/images/imagelists.txt");
    string s;
    while(getline(in,s))//着行读取数据并存于s中，直至数据全部读取
    {
        cout<<s.c_str()<<endl;
        imageLists.push_back(s);
    }
    in.close();
}

int main(int argc, char **argv) {
    loadImages();
    VideoCapture capture;
    //std::cout << "Hello, world!" << std::endl;
    ofstream out("/Users/abc/work/opencvTest/images/imagelists.txt",ios::app);
    FaceDetector fd("/Users/abc/work/opencvTest/opencvTest/models", FaceDetector::MODEL_V1);
    
    FaceRecognizerWrap faceRecog;
    try{
    int idx= 1;
    Mat gray;
    
    for(std::vector<string>::const_iterator iter = imageLists.begin();iter!= imageLists.end();++iter)
    {
        gray = imread(*iter);
        cvtColor(gray, gray, CV_RGB2GRAY);
        faceRecog.LoadFrame(gray,idx);
        idx++;

    }
    
    faceRecog.InitLBPHTrain();
    }
    catch(Exception ex)
    {
        std::cout <<ex.msg<<endl;
    }
//    Mat testImage = imread("/Users/abc/work/opencvTest/images/image_1493479329778.jpg");
//    cvtColor(testImage, testImage, CV_RGB2GRAY);
//   int res = faceRecog.LBPHPredict(testImage);
//
    
    
    
    Mat frame, image,grayImg;
    capture.open(0);
    Mat imageROI;
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
            
            
            
//            cout<< "detected face NUM : " << res.size() << endl;
            for(int k = 0; k < res.size(); k++)
            {
                try{
                    cv::rectangle(frame1, cv::Point(res[k].x1, res[k].y1), cv::Point(res[k].x2, res[k].y2), cv::Scalar(0, 255, 255), 2);
                    
                    //这个地方 要注意下 保证样本的宽和高，下面的代码里面会用到这份样本作为保存的训练样本！！！！！！！！demo代码，没做保证。
                    imageROI = frame1(Rect(res[k].x1, res[k].y1, sqrt(pow(res[k].x2 - res[k].x1,2)),sqrt(pow(res[k].y2 - res[k].y1,2))));
                    cv::resize(imageROI, imageROI, cv::Size(300, 300), (0, 0), (0, 0), cv::INTER_LINEAR);
                }
                catch(Exception ex)
                {
                    std::cout <<"create image failed:" << ex.msg.c_str()<<std::endl;
                }
                int label;
                double confidence;
                
                cv::imshow("testimageROI", imageROI);
                cvtColor(imageROI, grayImg, CV_RGB2GRAY);
                
                try{
                   faceRecog.LBPHPredict(grayImg, label, confidence);
                }catch(Exception ex)
                {
                    std::cout <<ex.msg.c_str() << std::endl;
                }
                std::cout<< "label:" << label << std::endl;
                std::cout << "confidence:" << confidence << std::endl;
                ///Users/abc/work/opencvTest/image
                char buffer[128];
                snprintf(buffer, sizeof(buffer), "/Users/abc/work/opencvTest/images/image_%ld.jpg",getTimeStamp());
                out<<buffer<<endl;
                imwrite( buffer, imageROI );
                //cv::waitKey();
                                //for(int i = 0; i < 5; i ++)
                //    cv::circle(frame1, cv::Point(res[k].points_x[i], res[k].points_y[i]), 2, cv::Scalar(0, 255, 255), 2);
            }
            cv::imshow("test", frame1);

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    out.close();
    
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
