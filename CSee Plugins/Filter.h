#ifndef __GST_ARFILTER_FILTER__
#define __GST_ARFILTER_FILTER__

#include <string>
#include "opencv2/opencv.hpp"

class Filter
{
private:
	std::string &name;
public:
	Filter(std::string&);
	virtual void process(cv::Mat&) = 0;
	std::string getName();
};

#endif /* __GST_ARFILTER_FILTER__ */