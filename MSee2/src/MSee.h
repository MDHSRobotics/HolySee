#ifndef __TEAM4141_MSEE__
#define __TEAM4141_MSEE__

#include <string>
#include <stdio.h>
#include "Config.h"

class MSee
{
private:
	std::string& instanceName;
	std::string& configFileName;
	Config* config = NULL;

public:
	MSee(std::string& instanceName, std::string& configFileName);
};

#endif /* __TEAM4141_MSEE__ */