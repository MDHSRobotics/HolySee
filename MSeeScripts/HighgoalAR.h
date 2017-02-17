#ifndef __GST_ARFILTER_FILTER_Highgoal_AR__
#define __GST_ARFILTER_FILTER_Highgoal_AR__


#include <vector>
#include <map>
#include <math.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Filter.h"

class HighgoalAR :
	public Filter
{
private:
	std::string name = std::string("HighgoalAR");
	cv::Mat hsvThresholdOutput;
		cv::Mat AROutput;
		std::vector<std::vector<cv::Point> > findContoursOutput;
		std::vector<std::vector<cv::Point> > filterContoursOutput;
		void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void findContours(cv::Mat &, bool , std::vector<std::vector<cv::Point> > &);
		void setsource(cv::Mat &source0);
		void makeMatFromContours(cv::Mat & source0);
		void filterContours(std::vector<std::vector<cv::Point> > &, double , double , double , double , double , double , double [], double , double , double , double , std::vector<std::vector<cv::Point> > &);
		cv::Mat source0;
		void makeMatFromContours(cv::Mat &,std::vector<std::vector<cv::Point> > &,cv::Mat &);
public:
    HighgoalAR();
	~HighgoalAR();
	void process(cv::Mat& source0);
		cv::Mat* gethsvThresholdOutput();
		cv::Mat* getARImage();
		cv::Mat*contoursImage();
		std::vector<std::vector<cv::Point> >* getfindContoursOutput();
		std::vector<std::vector<cv::Point> >* getfilterContoursOutput();

};

#endif /* __GST_ARFILTER_FILTER_Highgoal_AR__ */
