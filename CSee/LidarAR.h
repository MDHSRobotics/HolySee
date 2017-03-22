#ifndef LIDARAR_H
#define LIDARAR_H

#include "Filter.h"

class LidarAR : public Filter
{
private:
	std::string name = std::string("lidarAR");
	bool first = true;
	double rho=1;
	double theta = CV_PI/180.0;
	int threshold=10;
	double minLength=50;
	double maxGap=40;
public:
	LidarAR();
	~LidarAR();
	void process(cv::Mat& frame);
	void setParameters(std::string& parameters);
	void setRho(double rho);
	void setTheta(double theta);
	void setThreshold(int threshold);
	void setMinLength(double minLength);
	void setMaxGap(double maxGap);
	double getRho();
	double getTheta();
	int getThreshold();
	double getMinLength();
	double getMaxGap();
};

#endif // LIDARAR_H
