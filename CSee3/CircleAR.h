#ifndef __GST_ARFILTER_FILTER_CIRCLE_AR__
#define __GST_ARFILTER_FILTER_CIRCLE_AR__

#include "Filter.h"

class CircleAR :
	public Filter
{
private:
	std::string name = std::string("circleAR");
public:
	CircleAR();
	~CircleAR();
	void process(cv::Mat&);

};

#endif /* __GST_ARFILTER_FILTER_CIRCLE_AR__ */