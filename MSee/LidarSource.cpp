#include "LidarSource.h"

LidarSource::LidarSource(std::string name, std::string device, std::string arName, std::string cvName) : Source(name,device,false,arName,cvName)
{

}

LidarSource::LidarSource(std::string name, std::string device, std::string arName, std::string arParameters, std::string cvName) : Source(name,device,false,arName,arParameters,cvName)
{

}

LidarSource::~LidarSource()
{
	
}

std::string LidarSource::getPipelineSegment(){
//	return std::string("videotestsrc pattern=ball ! video/x-raw,width=640,height=480,framerate=15/1,format=BGR ! videoconvert");
    std::string sourceElement("lidarsrc device=/dev/ttyUSB0 ");
	sourceElement.append("simulate=true ");
//	sourceElement.append("simulate=false ");
//  sourceElement("recordTo=/tmp/lidar.dat ");
//  sourceElement("readFrom=/tmp/lidar.dat ");
	sourceElement.append("! lidarimg ");
	sourceElement.append("style=simple ");
//	sourceElement.append("style=graduated ");
	sourceElement.append("! video/x-raw,width=640,height=480,format=GRAY8,framerate=5/1 ");
    devSwap(sourceElement, device);
	return std::string(sourceElement);
}
