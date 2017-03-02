#ifndef __TEAM4141_MSEE__
#define __TEAM4141_MSEE__

#include <string>
#include <stdio.h>
#include "Config.h"
#include "Streamer.h"
#include "easywsclient.hpp"
#include "Poco/JSON/Parser.h"

class MSee
{
private:
	std::string& instanceName;
	std::string& configFileName;
	std::string robotURI;
	Config* config = NULL;
	
public:
	static Streamer* streamer;
	static unsigned char currentChannel;
	static unsigned char channelCount;
	MSee(int argc,char**argv,std::string& instanceName, std::string& configFileName);
	void start();
	void stop();
	static void switchTo(int);
	int getChannelCount();
	void robotDiscovered(std::string&);
	std::string& getRobotURI();
	void setRobotURI(std::string&);
};

#endif /* __TEAM4141_MSEE__ */
