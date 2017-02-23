#ifndef __GST_ARFILTER_FILTER_SQUARE_AR__
#define __GST_ARFILTER_FILTER_SQUARE_AR__

#include "Filter.h"

class SquareAR :
	public Filter
{
private:
	std::string name=std::string("squareAR");
public:
	SquareAR();
	~SquareAR();
	void process(cv::Mat&);

};

#endif /* __GST_ARFILTER_FILTER_SQUARE_AR__ */