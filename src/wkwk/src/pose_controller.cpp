//make reset button
//make start button
//make sequential program per QR

//hw/cam_nav
//hw/cam_dock

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
int x_init=0;
int y_init=180;
int Noise 	= 15;

void imageProcessing(Mat input_image);

Mat nav_image;
Mat dock_image;

void navCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{
  try
  {
    nav_image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
    waitKey(10);
    imageProcessing(nav_image);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert to image!");
  }
}

/*
void dockCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{
  try
  {
    dock_image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
    waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert to image!");
  }
}
*/

int main(int argc, char **argv){
	ros::init(argc, argv, "pose");
	ros::NodeHandle nh;
	cv::startWindowThread();
	
	image_transport::ImageTransport it(nh);
	
	ros::Subscriber sub_nav 	= nh.subscribe("/hw/cam_nav", 1, navCallback);
	//ros::Subscriber sub_dock 	= nh.subscribe("/hw/cam_dock", 1, dockCallback);

	namedWindow("panel", CV_WINDOW_AUTOSIZE);
	
	createTrackbar("x", "panel", &x_init, 700); //Hue (0 - 255)
	createTrackbar("y", "panel", &y_init, 700);
	createTrackbar("width", "panel", &width, 700); //Saturation (0 - 255)
	createTrackbar("hight", "panel", &height, 700);
	createTrackbar("noise", "panel", &Noise, 255);
	
	while (ros::ok()) {
		ros::spinOnce();
		//imageProcessing(dock_image);
	}
}

void imageProcessing(Mat input_image){
	/*
	Rect region_of_interest = Rect(x_init, y_init, width, height);
	Mat Original = input_image(region_of_interest);
	
	Size sz = Original.size();
	int original_height = sz.height; 
	int original_width	= sz.width;
		
	line( input_image, Point( x_init, y_init ), Point( x_init+original_width, y_init), Scalar( 100, 100, 100 ), 2, 8 );
	line( input_image, Point( x_init, y_init+original_height ), Point( x_init+original_width, y_init+original_height), Scalar( 100, 100, 100 ), 2, 8 );	
	line( input_image, Point( x_init, y_init ), Point( x_init, y_init+original_height), Scalar( 100, 100, 100 ), 2, 8 );
	line( input_image, Point( x_init+original_width, y_init ), Point( x_init+original_width, y_init+original_height), Scalar( 100, 100, 100 ), 2, 8 );
	*/
	imshow("Input_QR", input_image);
}
