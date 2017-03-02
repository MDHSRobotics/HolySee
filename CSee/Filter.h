#ifndef __GST_ARFILTER_FILTER__
#define __GST_ARFILTER_FILTER__

#include <string>
#include "opencv2/opencv.hpp"
#include "gst/gst.h"


class Filter
{
private:
	std::string &name;
	GstBus* bus;
public:
	Filter(std::string&);
	virtual void process(cv::Mat&) = 0;
	std::string& getName();
	void setBus(GstBus* bus);
	void post(GstStructure *);
	void postBooleanEvent(std::string eventName, bool eventData);
	void postStringEvent(std::string eventName, std::string eventData);
	void postIntEvent(std::string eventName, int eventData);
	void postDoubleEvent(std::string eventName, double eventData);
	
};

#endif /* __GST_ARFILTER_FILTER__ */
