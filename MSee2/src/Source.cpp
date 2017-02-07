#include "Source.h"


Source::Source(std::string name, std::string device, bool showRaw, std::string arName, std::string cvName): name(name), device(device), _showRaw(showRaw), arName(arName), cvName(cvName)
{

	if (this->showRaw()){
		connectionNames.push_back(std::string(name + ".raw"));
		channelNames.push_back(std::string(name + ".raw"));
	}
	if (this->hasAR()){
		connectionNames.push_back(std::string(name + "." + arName));
		channelNames.push_back(std::string(name + "." + arName));
	}
	if (this->hasCV()){
		connectionNames.push_back(std::string(name + "." + cvName));
	}

}

Source::~Source()
{
}

std::string Source::getName(){
	return name;
}

std::string Source::getDevice(){
	return device;
}
std::string Source::getARName(){
	return arName;
}

std::string Source::getCVName(){
	return cvName;
}

bool Source::showRaw(){
	return _showRaw;
}
bool Source::hasAR(){
	return !arName.empty();
}
bool Source::hasCV(){
	return !cvName.empty();
}

int Source::countConnections(){
	return connectionNames.size();
}

int Source::countChannels(){
	return channelNames.size();
}

std::vector< std::string> Source::getChannelNames(){
	return channelNames;
}
std::vector<std::string> Source::getConnectionNames(){
	return connectionNames;
}
