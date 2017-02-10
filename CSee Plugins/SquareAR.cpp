#include "SquareAR.h"


SquareAR::SquareAR() : Filter(name)
{
}


SquareAR::~SquareAR()
{
}

void SquareAR::process(cv::Mat& frame){
	cv::rectangle(frame, cv::Point(frame.cols / 10, frame.rows / 10), cv::Point(frame.cols - frame.cols / 10, frame.rows - frame.rows / 10), cv::Scalar(255, 255, 255), 4, CV_AA, 0);
}
