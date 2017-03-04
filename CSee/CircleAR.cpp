#include "CircleAR.h"


CircleAR::CircleAR() : Filter(name)
{
}


CircleAR::~CircleAR()
{
}

void CircleAR::process(cv::Mat& frame){
	cv::circle(frame, cv::Point(frame.cols / 2, frame.rows / 2), (frame.cols >= frame.rows ? frame.cols/ 4 : frame.rows / 4), cv::Scalar(255, 255, 255, 0.4), 3, CV_AA, 0);
//	if (first){
//		printf("processing cirle\n");
//		first = false;
//		GstStructure *msgStruct = gst_structure_new("filterpostevent", "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_STRING , "circling ...", NULL);
//		post(msgStruct);  //test posting capability 
//		postBooleanEvent("targetAcquired", true); //test posting capability
//	}
}
