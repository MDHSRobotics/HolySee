#include "VideoSource.h"


VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string arParameters, std::string cvName) : Source(name, deviceName, showRaw, arName, arParameters, cvName)
{
}
VideoSource::VideoSource(std::string name, std::string deviceName, bool showRaw, std::string arName, std::string arParameters, std::string cvName,std::string sourceElement) : Source(name, deviceName, showRaw, arName, arParameters, cvName),sourceElement(sourceElement)
{
}


std::string VideoSource::getPipelineSegment(){
	std::string segment;
    devSwap(sourceElement, device);
	segment.append(sourceElement);
	segment.append(" ");
	//segment.append(device);
	segment.append(" ! video/x-raw,width=640,height=480,format=RGBA");
    //segment.append(" ! video/x-raw,width=640,height=480,framerate=30/1,format=RGBA");
	return segment;
}

VideoSource::~VideoSource()
{
}

