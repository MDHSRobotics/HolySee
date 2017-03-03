#ifndef __TEAM4141_MSEE__
#define __TEAM4141_MSEE__

#include <string>
#include <stdio.h>
#include <queue>
#include "Config.h"
#include "easywsclient.hpp"
#include "Poco/JSON/Parser.h"
class Streamer;

class MSee
{
private:
	std::string& instanceName;
	std::string& configFileName;
	std::string robotURI;
	Config* config = NULL;
	std::queue<std::string> outqueue;

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
	void targetAcquiredUpdate(std::string filter, bool targetAcquired);
	void post(std::string message);
	bool hasMessages();
	std::string nextMessage();
};

#endif /* __TEAM4141_MSEE__ */
