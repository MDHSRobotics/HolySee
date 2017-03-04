#include "LidarSource.h"

LidarSource::LidarSource(std::string name, std::string device, std::string arName, std::string cvName) : Source(name,device,true,arName,cvName)
{

}

LidarSource::~LidarSource()
{
	
}

std::string LidarSource::getPipelineSegment(){
//	return std::string("videotestsrc pattern=ball ! video/x-raw,width=640,height=480,framerate=15/1,format=BGR ! videoconvert");
	return std::string("lidarsrc device=/dev/ttyUSB0 simulate=true ! lidarimg ! video/x-raw,width=640,height=480,format=GRAY8,framerate=5/1 ");
}
