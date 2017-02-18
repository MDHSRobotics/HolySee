/*
 * CV2.0.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: x
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Grip2.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	  if( argc != 2)
	    {
	      printf( "invalid arguments \n" );
	      return -1;
	    }
	  Mat image;
	  image = imread( argv[1], 1 );
	  //cv::rectangle(image,Point(384,290),Point(350,400),Scalar(255),2,8,0);
	  //cv::rectangle(image,Point(6,600),Point(100,400),Scalar(255),2,8,0);
	  if( !image.data )
	    {
	      printf( "No image data \n" );
	      return -1;

	    }

      namedWindow ("Display window",CV_WINDOW_AUTOSIZE);
      std::vector<cv::Rect> targets;
      targets.push_back(cv::Rect(360,70,60,40));
	  targets.push_back(cv::Rect(360,40,80,50));
      Grip2 filter(targets);

      		filter.process(image);
      		imshow (" Display window", *(filter.getARImage()));



      waitKey(0);
	  return 0;

  }






