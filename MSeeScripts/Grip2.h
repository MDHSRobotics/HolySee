#ifndef SRC_GRIP2_H_
#define SRC_GRIP2_H_

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

class Grip2 {
public:

private:
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
	std::vector<cv::Rect>& targets;
public:
	Grip2(std::vector<cv::Rect>&);
	virtual ~Grip2();
	void process(cv::Mat& source0);
	cv::Mat* gethsvThresholdOutput();
	cv::Mat* getARImage();
	cv::Mat*contoursImage();
	std::vector<std::vector<cv::Point> >* getfindContoursOutput();
	std::vector<std::vector<cv::Point> >* getfilterContoursOutput();
};

#endif /* SRC_GRIP2_H_ */
