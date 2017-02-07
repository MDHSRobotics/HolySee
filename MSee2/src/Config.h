#ifndef __TEAM4141_MSEE_CONFIG_
#define __TEAM4141_MSEE_CONFIG_

#include <map>
#include <vector>
#include <string>

#include "Poco/Util/PropertyFileConfiguration.h"


using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

class Config
{
private:
	std::string& configFileName;
	std::string& configRoot;
	std::vector<std::string> nodes;
	std::map<std::string, std::string> identifierMap;
	AutoPtr<PropertyFileConfiguration> pConf;
	void parseNodes();
	void discover(std::string&, std::string&);
	void discoverUSB(std::string&);
	void discoverCameras(std::string&);

public:
	Config(std::string&, std::string&);
	std::string get(std::string&);
	std::vector<std::string> getNodes();
};

#endif /*__TEAM4141_MSEE_CONFIG_*/