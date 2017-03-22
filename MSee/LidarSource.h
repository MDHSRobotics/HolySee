#ifndef __TEAM4141_MSEE_LIDARSOURCE__
#define __TEAM4141_MSEE_LIDARSOURCE__

#include "Source.h"
#include <string>

class LidarSource :
	public Source
{
private:

public:
	LidarSource(std::string name, std::string device, std::string arName, std::string cvName);
	LidarSource(std::string name, std::string device, std::string arName, std::string arParameters, std::string cvName);
	~LidarSource();
	std::string getPipelineSegment();
};

#endif /* __TEAM4141_MSEE_LIDARSOURCE__ */
