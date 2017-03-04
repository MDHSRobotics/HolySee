#include "VideoSource.h"


VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string cvName) : Source(name, deviceName, showRaw, arName, cvName)
{
}
VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string cvName,std::string sourceElement) : Source(name, deviceName, showRaw, arName, cvName),sourceElement(sourceElement)
{
}


std::string VideoSource::getPipelineSegment(){
	std::string segment;
	segment.append(sourceElement);
	segment.append(" ");
	//segment.append(device);
	segment.append(" ! video/x-raw,width=640,height=480,framerate=30/1,format=RGBA");
	return segment;
}

VideoSource::~VideoSource()
{
}

