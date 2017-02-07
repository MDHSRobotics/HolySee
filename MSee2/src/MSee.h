#ifndef __TEAM4141_MSEE__
#define __TEAM4141_MSEE__

#include <string>
#include <stdio.h>
#include "Config.h"
#include "Streamer.h"

class MSee
{
private:
	std::string& instanceName;
	std::string& configFileName;
	Config* config = NULL;
	Streamer* streamer = NULL;

public:
	MSee(std::string& instanceName, std::string& configFileName);
	void start();
	void stop();
	void switchTo(int);
	int getChannelCount();
};

#endif /* __TEAM4141_MSEE__ */
