#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int width = 640;
int height = 200;
int x_init_red=0;
int y_init_red=180;
int Noise_red 	= 15;


void imageProcessing(Mat input_image);

Mat receive_image;

void imageCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{
  try
  {
    receive_image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
    waitKey(10);
    imageProcessing(receive_image);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert to image!");
  }
}

int main(int argc, char **argv){
	ros::init(argc, argv, "pose");
	ros::NodeHandle nh;
	cv::startWindowThread();
	
	image_transport::ImageTransport it(nh);
	
	ros::Subscriber sub = nh.subscribe("camera/image/compressed", 1, imageCallback);

	namedWindow("panel", CV_WINDOW_AUTOSIZE);
	
	createTrackbar("x", "panel", &x_init_red, 700); //Hue (0 - 255)
	createTrackbar("y", "panel", &y_init_red, 700);
	createTrackbar("width", "panel", &width, 700); //Saturation (0 - 255)
	createTrackbar("hight", "panel", &height, 700);
	createTrackbar("noise", "panel", &Noise_red, 255);
	
	while (ros::ok()) {
		ros::spinOnce();
	}
}

void imageProcessing(Mat input_image){
	Mat imgOriginal, imgHSV, imgThresholded, imgErode, imgDilate, imgDebug;
	
	imgDebug = input_image.clone();
	medianBlur(imgDebug, imgDebug, 5);
	
	erode(imgDebug, imgDebug, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) );
	dilate( imgDebug, imgDebug, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
	dilate(imgDebug, imgDebug, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
	erode(imgDebug, imgDebug, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
	
	Rect region_of_interest = Rect(x_init_red, y_init_red, width, height);
	Mat Original = input_image(region_of_interest);
	
	Size sz = Original.size();
	int original_height = sz.height; 
	int original_width	= sz.width;
	
	Size sx = input_image.size();
	int input_height = sx.height;
	int input_width = sx.width; 
	
	imgOriginal = Original.clone();
	
	medianBlur(imgOriginal, imgOriginal, 5);
			
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) );
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
		
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(Noise_red, Noise_red)) ); 
	
	line( input_image, Point( x_init_red, y_init_red ), Point( x_init_red+original_width, y_init_red), Scalar( 100, 100, 100 ), 2, 8 );
	line( input_image, Point( x_init_red, y_init_red+original_height ), Point( x_init_red+original_width, y_init_red+original_height), Scalar( 100, 100, 100 ), 2, 8 );	
	line( input_image, Point( x_init_red, y_init_red ), Point( x_init_red, y_init_red+original_height), Scalar( 100, 100, 100 ), 2, 8 );
	line( input_image, Point( x_init_red+original_width, y_init_red ), Point( x_init_red+original_width, y_init_red+original_height), Scalar( 100, 100, 100 ), 2, 8 );
	
	//imshow("Threshold_Red", imgThresholded);
	//imshow("Input_Red", input_image);
	//imshow("Roi_Red", Original);
	//imshow("All_Red", imgDebug);
}
