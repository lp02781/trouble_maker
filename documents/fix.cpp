//preprocessor
#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>

//namespace
using namespace cv;
using namespace std;

//matrix
Mat imgOriginal;

void display(Mat &im, Mat &bbox)
{
  int n = bbox.rows;
  for(int i = 0 ; i < n ; i++)
  {
    line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
  }
}

int main( int argc, char** argv )
{
	VideoCapture cap(0);//webcam
	
	if ( !cap.isOpened() )  // jika tidak terbaca, exit
    {
         cout << "webcam tidak terbaca" << endl;
         return -1;
    }
	
	cap.read(imgOriginal);//capture di imgOriginal
    namedWindow("ColourTracking", CV_WINDOW_AUTOSIZE);//nama window
	
	
	while (true)//loop sampai exit
    {
		bool bSuccess = cap.read(imgOriginal); // membaca frame baru dari video
		if (!bSuccess) //jika tidak sukses, menghentikan loop
        {
             cout << "tidak bisa membaca frame dari video" << endl;
             break;
        }
        
        QRCodeDetector qrDecoder;
 
		Mat bbox, rectifiedImage;
 
		std::string data = qrDecoder.detectAndDecode(imgOriginal, bbox, rectifiedImage);
		if(data.length()>0)
		{
			cout << "Decoded Data : " << data << endl;
 
			display(imgOriginal, bbox);
			rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
		}
		else cout << "QR Code not detected" << endl;
		
		
		//menampilkan image
		imshow("Original", imgOriginal); 
        
        if (waitKey(30) == 27) //exit esc
        {
            cout << "esc di tekan" << endl;
            break; 
        }
	}
	return 0;
}
