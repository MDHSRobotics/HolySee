#include "CircleAR.h"


CircleAR::CircleAR() : Filter(name)
{
}


CircleAR::~CircleAR()
{
}

void CircleAR::process(cv::Mat& frame){
	cv::circle(frame, cv::Point(frame.cols / 2, frame.rows / 2), (frame.cols >= frame.rows ? frame.cols/ 4 : frame.rows / 4), cv::Scalar(255, 255, 255, 0.4), 3, CV_AA, 0);
}
