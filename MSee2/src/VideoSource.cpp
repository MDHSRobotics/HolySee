#include "VideoSource.h"


VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string cvName) : Source(name, deviceName, showRaw, arName, cvName)
{
}

VideoSource::~VideoSource()
{
}

std::string VideoSource::getPipelineSegment(){
	std::string segment;
	segment.append("v4l2src ");
	//segment.append(device);
	segment.append(" ! video/x-raw,width=640,framerate=15/1,format=BGR");
	return segment;
}
