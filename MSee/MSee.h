#ifndef __TEAM4141_MSEE__
#define __TEAM4141_MSEE__

#include <string>
#include <stdio.h>
#include "Config.h"
#include "Streamer.h"
#include "easywsclient.hpp"


class MSee
{
private:
	std::string& instanceName;
	std::string& configFileName;
	std::string robotURI;
	Config* config = NULL;
	Streamer* streamer = NULL;


public:
	MSee(int argc,char**argv,std::string& instanceName, std::string& configFileName);
	void start();
	void stop();
	void switchTo(int);
	int getChannelCount();
	void robotDIscovered(std::string&);
	std::string& getRobotURI();
	void setRobotURI(std::string&);
};

#endif /* __TEAM4141_MSEE__ */
