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

void imageProcessing(Mat input_nav_image, Mat input_dock_image);

Mat nav_image;
Mat dock_image;

void navCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
	nav_image = cv_bridge::toCvShare(msg, "bgr8")->image;
	waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert to image!");
  }
}

void dockCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    dock_image = cv_bridge::toCvShare(msg, "bgr8")->image;
    waitKey(10);
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
	
	ros::Subscriber sub_nav 	= nh.subscribe("/hw/cam_nav", 8, navCallback);
	ros::Subscriber sub_dock 	= nh.subscribe("/hw/cam_dock",8, dockCallback);

	namedWindow("panel", CV_WINDOW_AUTOSIZE);
	
	while (ros::ok()) {
		ros::spinOnce();
		imageProcessing(nav_image, dock_image);		
	}
}

void imageProcessing(Mat input_nav_image, Mat input_dock_image){	
	imshow("nav_image", input_nav_image);
	imshow("dock_image", input_dock_image);
}
