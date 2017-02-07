#include "stdafx.h"
#include "MSee.h"


MSee::MSee(std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName)
{
	config = new Config(instanceName, configFileName);
}
