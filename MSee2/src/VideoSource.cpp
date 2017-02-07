#include "VideoSource.h"


VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string cvName) : Source(name, deviceName, showRaw, arName, cvName)
{
}

VideoSource::~VideoSource()
{
}

std::string VideoSource::getPipelineSegment(){
	std::string segment;
	segment.append("autovideosrc ");
	//segment.append(device);
	segment.append(" ! videoconvert ! video/x-raw,width=640,framerate=15/1,format=GRAY8 ! videoconvert");
	return segment;
}
