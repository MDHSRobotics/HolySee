/*
 * Grip2.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: x
 */

#include "Grip2.h"
#include <stdio.h>





Grip2::Grip2(std::vector<cv::Rect>& targets): targets(targets) {
	// TODO Auto-generated constructor stub

}

Grip2::~Grip2() {
	// TODO Auto-generated destructor stub
}

void Grip2::process(cv::Mat& source0){
	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThresholdInput = source0;
	double hsvThresholdHue[] = {17.805755395683452, 90.92150170648463};
	double hsvThresholdSaturation[] = {185.74640287769785, 255.0};
	double hsvThresholdValue[] = {27.51798561151079, 150.5631399317406};
	hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput);
	//Step Find_Contours0:
	//input
	cv::Mat findContoursInput = hsvThresholdOutput;
	bool findContoursExternalOnly = false ;  // default Boolean
	findContours(findContoursInput, findContoursExternalOnly, this->findContoursOutput);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput;
	double filterContoursMinArea = 125.0;  // default Double
	double filterContoursMinPerimeter = 0.0;  // default Double
	double filterContoursMinWidth = 0.0;  // default Double
	double filterContoursMaxWidth = 1000.0;  // default Double
	double filterContoursMinHeight = 0.0;  // default Double
	double filterContoursMaxHeight = 1000.0;  // default Double
	double filterContoursSolidity[] = {0, 100.0};
	double filterContoursMaxVertices = 1000000.0;  // default Double
	double filterContoursMinVertices = 0.0;  // default Double
	double filterContoursMinRatio = 0.0;  // default Double
	double filterContoursMaxRatio = 1000.0;  // default Double
	filterContours(filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);

	//wew have our desired countours
	makeMatFromContours(source0,this->filterContoursOutput,this->AROutput);
}


void Grip2::makeMatFromContours(cv::Mat & original,std::vector<std::vector<cv::Point> > & contours,cv::Mat &arImage){
//loop through contours
	arImage = original;

    cv::Scalar color_bad(0,0,255);  //red
    cv::Scalar color_good(0,255,0); //green

    bool IAmGood= true;
    printf(("testing bb in targets\n"));

    for(int c=0;c<contours.size();c++){
        printf("testing bb %d\n",c);
		std::vector<cv::Point> contour =contours.at(c);
	    bool IAmInTarget= false;
	    cv::Rect bb = cv::boundingRect(contour);
		for (cv::Rect t : targets){
	        printf("testing target bbx1:%d,tx1:%d, bby1:%d,ty1:%d, bbx2:%d,tx2:%d, bby2:%d,ty2:%d, fit:%s\n",
	        		bb.x,t.x,bb.y,t.y,bb.x+bb.width,t.width+t.x,bb.y+bb.height,t.height+t.y,
					((
							bb.x>=t.x &&
							bb.y>=t.y &&
							bb.x+bb.width <= t.width+t.x &&
							bb.y+bb.height <= t.height+t.y)?"true":"false")
					);
		    if (
				bb.x>=t.x &&
				bb.y>=t.y &&
				bb.x+bb.width <= t.width+t.x &&
				bb.y+bb.height <= t.height+t.y)
			{
				IAmInTarget=true;
                break;
			}
		}
		if (!IAmInTarget){
			IAmGood=false;
		    break;
		}
	}
    printf((IAmGood?"IAmGood\n":"bummer ...\n"));

	for(int c=0;c<contours.size();c++){
		std::vector<cv::Point> contour =contours.at(c);

		//loop through points
		for(int p=0;p<contour.size();p++){
				cv::Point point=contour.at(p);
				cv::circle(arImage,point,2,(IAmGood?color_good:color_bad),2,CV_AA,0);
		}

		//for each contour draw boundingRect
		cv::Rect bb = cv::boundingRect(contour);
		printf("contour %d Rect(%d,%d,%d,%d)\n",c,bb.x,bb.y,bb.width,bb.height);
		cv::rectangle(arImage,bb,(IAmGood?color_good:color_bad),2,CV_AA,0);
	}




	for (cv::Rect t : targets){
		cv::rectangle(arImage,t,cv::Scalar(255,255,255),2,CV_AA,0);
	}


}


void Grip2::setsource(cv::Mat &source0){
	source0.copyTo(this->source0);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* Grip2::gethsvThresholdOutput(){
	return &(this->hsvThresholdOutput);
}


/**
 * This method is a generated getter for the output of AR Image.
 * @return Mat output from AROutput.
 */
cv::Mat* Grip2::getARImage(){
	return &(this->AROutput);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */

std::vector<std::vector<cv::Point> >* Grip2::getfindContoursOutput(){
	return &(this->findContoursOutput);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* Grip2::getfilterContoursOutput(){
	return &(this->filterContoursOutput);
}
	/**
	 * Segment an image based on hue, saturation, and value ranges.
	 *
	 * @param input The image on which to perform the HSL threshold.
	 * @param hue The min and max hue.
	 * @param sat The min and max saturation.
	 * @param val The min and max value.
	 * @param output The image in which to store the output.
	 */
	void Grip2::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
	}

	/**
	 * Finds contours in an image.
	 *
	 * @param input The image to find contours in.
	 * @param externalOnly if only external contours are to be found.
	 * @param contours vector of contours to put contours in.
	 */
	void Grip2::findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
		std::vector<cv::Vec4i> hierarchy;
		contours.clear();
		int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
		int method = cv::CHAIN_APPROX_SIMPLE;
		cv::findContours(input, contours, hierarchy, mode, method);
	}


	/**
	 * Filters through contours.
	 * @param inputContours is the input vector of contours.
	 * @param minArea is the minimum area of a contour that will be kept.
	 * @param minPerimeter is the minimum perimeter of a contour that will be kept.
	 * @param minWidth minimum width of a contour.
	 * @param maxWidth maximum width.
	 * @param minHeight minimum height.
	 * @param maxHeight  maximimum height.
	 * @param solidity the minimum and maximum solidity of a contour.
	 * @param minVertexCount minimum vertex Count of the contours.
	 * @param maxVertexCount maximum vertex Count.
	 * @param minRatio minimum ratio of width to height.
	 * @param maxRatio maximum ratio of width to height.
	 * @param output vector of filtered contours.
	 */

	void Grip2::filterContours(std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter, double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[], double maxVertexCount, double minVertexCount, double minRatio, double maxRatio, std::vector<std::vector<cv::Point> > &filterContoursOutput){
			std::vector<cv::Point> hull;
			filterContoursOutput.clear();
			{



				printf ("number of contours: %d\n",inputContours.size());
							for(int i=0;i<inputContours.size();i++){
       							std::vector<cv::Point> contour = inputContours.at(i);
								cv::Rect bb = boundingRect(contour);
								if (bb.width < minWidth || bb.width > maxWidth) continue;
								if (bb.height < minHeight || bb.height > maxHeight) continue;
								double area = cv::contourArea(contour);
								if (area < minArea) continue;
								if (arcLength(contour, true) < minPerimeter) continue;
								cv::convexHull(cv::Mat(contour, true), hull);
								double solid = 100 * area / cv::contourArea(hull);
								if (solid < solidity[0] || solid > solidity[1]) continue;
								if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
							    double ratio = bb.width / bb.height;
								if (ratio < minRatio || ratio > maxRatio) continue;

								filterContoursOutput.push_back(contour );



							}
							printf ("number of contours: %d\n",filterContoursOutput.size());


			}
	}





