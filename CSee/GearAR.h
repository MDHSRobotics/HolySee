/*
 * GearAR.h
 *
 *  Created on: Feb 21, 2017
 *      Author: team4141
 */

#ifndef __GST_ARFILTER_FILTER_GEAR_AR_H__
#define __GST_ARFILTER_FILTER_GEAR_AR_H__

#include "Filter.h"

class GearAR :
		public  Filter
{
	private:
	std::string name = std::string("gearAR");
		std::vector<cv::Rect> targets;
	    cv::Scalar RED = cv::Scalar(0,0,255);  //red
	    cv::Scalar GREEN = cv::Scalar(0,255,0); //green
	    cv::Scalar WHITE = cv::Scalar(255,255,255);  //white
		cv::Mat AROutput;
	    //-------------  from GRIP
		cv::Mat hsvThresholdOutput;
		std::vector<std::vector<cv::Point> > findContoursOutput;
		std::vector<std::vector<cv::Point> > filterContoursOutput;
		void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void findContours(cv::Mat &, bool , std::vector<std::vector<cv::Point> > &);
		void makeMatFromContours(cv::Mat & source0);
		void filterContours(std::vector<std::vector<cv::Point> > &, double , double , double , double , double , double , double [], double , double , double , double , std::vector<std::vector<cv::Point> > &);
		void makeMatFromContours(cv::Mat &,std::vector<std::vector<cv::Point> > &,cv::Mat &);

public:
	GearAR();
	virtual ~GearAR();
	void process(cv::Mat&);
		cv::Mat* gethsvThresholdOutput();
		cv::Mat* getARImage();
		cv::Mat*contoursImage();
		std::vector<std::vector<cv::Point> >* getfindContoursOutput();
		std::vector<std::vector<cv::Point> >* getfilterContoursOutput();
};

#endif /* __GST_ARFILTER_FILTER_GEAR_AR_H__ */
