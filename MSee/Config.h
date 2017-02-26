#ifndef __TEAM4141_MSEE_CONFIG_
#define __TEAM4141_MSEE_CONFIG_

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Poco/Util/PropertyFileConfiguration.h"

#include "Source.h"

#define AR_TOKEN std::string("AR")
#define CV_TOKEN std::string("CV")

using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

class Config
{
private:
	std::string& configFileName;
	std::string& configRoot;
	std::vector<std::string> nodes;
	std::map<std::string, std::string> identifierMap;
	std::map<std::string, std::shared_ptr<Source>> devices;
	AutoPtr<PropertyFileConfiguration> pConf;
	void parseNodes();
	void discoverUSB(std::string&);
	void discoverCameras(std::string&);
	std::string pipelineDefinition;
	void createPipelineDefinition();

public:
	Config(std::string&, std::string&);
	std::string get(std::string&);
	std::vector<std::string> getNodes();
	std::map<std::string, std::shared_ptr<Source>> getDevices();
	std::string getPipelineDefinition();
	static void discover(std::string&, std::string&);
	static std::vector<std::string> split(const char *, char&);
};

#endif /*__TEAM4141_MSEE_CONFIG_*/
