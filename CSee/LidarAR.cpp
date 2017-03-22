#include "LidarAR.h"

LidarAR::LidarAR(): Filter(name)
{
}

LidarAR::~LidarAR()
{
}

void LidarAR::process(cv::Mat& frame){
	if (first){
		printf("processing lidar\n");
		first = false;
		GstStructure *msgStruct = gst_structure_new("filterpostevent", "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_STRING , "circling ...", NULL);
		post(msgStruct);  //test posting capability 
		postBooleanEvent("targetAcquired", true); //test posting capability
	}
	
	//try to use Hough Line Transform to detect lines in lidar image
	cv::Mat gray_image;  //get a grayscale version of the image
	cvtColor(frame,gray_image,CV_BGR2GRAY);
	
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(gray_image,lines,getRho(),getTheta(),getThreshold(),getMinLength(),getMaxGap());
	printf("%d lines detected\n",lines.size());
	for(size_t i=0;i<lines.size();i++){
		cv::line(frame,cv::Point(lines[i][0],lines[i][1]),
				cv::Point(lines[i][2],lines[i][3]), cv::Scalar(180,40,40),3,CV_AA);
	}
	
	//show a circle to know the filter is active
	cv::circle(frame, cv::Point(frame.cols / 2, frame.rows / 2), (frame.cols >= frame.rows ? frame.cols/ 4 : frame.rows / 4), cv::Scalar(100, 100, 200), 1, CV_AA, 0);

}

std::vector<std::string> split(const char *str, char& delimiter)
{
	std::vector<std::string> result;

	do
	{
		const char *begin = str;

		while (*str != delimiter && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}

const std::string TOKEN_RHO("rho");
const std::string TOKEN_THETA("theta");
const std::string TOKEN_THRESHOLD("threshold");
const std::string TOKEN_MINLENGTH("minLength");
const std::string TOKEN_MAXGAP("maxGap");

void LidarAR::setParameters(std::string& parameters){
	char paramDelim=';';
	char fieldDelim='=';
	Filter::setParameters(parameters);
	if(!getParameters().empty()){
		//printf("params: %s\n",getParameters().c_str());
		std::vector<std::string> params = split(getParameters().c_str(),paramDelim);
		for(std::string param : params){
			//printf("param: %s\n",param.c_str());
			std::vector<std::string> fields = split(param.c_str(),fieldDelim);
			if(fields[0] == TOKEN_RHO){
				setRho(std::stod(fields[1]));
				printf("%s=%s\n",fields[0].c_str(),fields[1].c_str());
			}
			else if(fields[0] == TOKEN_THRESHOLD){
				setThreshold(std::stoi(fields[1]));
				printf("%s=%s\n",fields[0].c_str(),fields[1].c_str());
			}
			else if(fields[0] == TOKEN_MINLENGTH){
				setMinLength(std::stod(fields[1]));
				printf("%s=%s\n",fields[0].c_str(),fields[1].c_str());
			}
			else if(fields[0] == TOKEN_MAXGAP){
				setMaxGap(std::stod(fields[1]));
				printf("%s=%s\n",fields[0].c_str(),fields[1].c_str());
			}
			else if(fields[0] == TOKEN_THETA){
				setTheta(std::stod(fields[1]));
				printf("%s=%s\n",fields[0].c_str(),fields[1].c_str());
			}
		}
	}
}

void LidarAR::setRho(double rho){
	this->rho = rho;
}

void LidarAR::setTheta(double thetaFactor){
	//nominal theta is CV_PI/180.0
	//theta factor is a scaling factor applied to nominal theta, default is 1.0
	this->theta = (CV_PI/180.0)*thetaFactor;
}

void LidarAR::setThreshold(int threshold){
	this->threshold = threshold;
}

void LidarAR::setMinLength(double minLength){
	this->minLength = minLength;
}

void LidarAR::setMaxGap(double maxGap){
	this->maxGap = maxGap;
}

double LidarAR::getRho(){
	return rho;
}

double LidarAR::getTheta(){
	return theta;
}

int LidarAR::getThreshold(){
	return threshold;
}

double LidarAR::getMinLength(){
	return minLength;
}

double LidarAR::getMaxGap(){
	return maxGap;
}