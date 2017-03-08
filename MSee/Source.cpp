#include "Source.h"


Source::Source(std::string name, std::string device, bool showRaw, std::string arName, std::string cvName): name(name), device(device), _showRaw(showRaw), arName(arName), cvName(cvName)
{

	if (this->showRaw()){
		connectionNames.push_back(std::string(name + "_raw"));
		channelNames.push_back(std::string(name + "_raw"));
	}
	if (this->hasAR()){
		connectionNames.push_back(std::string(name + "_" + arName));
		channelNames.push_back(std::string(name + "_" + arName));
	}
	if (this->hasCV()){
		connectionNames.push_back(std::string(name + "_" + cvName));
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
#define DEVICE_TOKEN std::string("/dev/")
void Source::devSwap(std::string& line, std::string&device){
	int pos = -1;
	pos = line.find(DEVICE_TOKEN);
	if (pos>=0){
		std::string result;
		int posEnd = line.find(" ", pos);
		result.append(line.substr(0, pos));
		result.append(device);
		result.append(line.substr(posEnd));
		line.clear();
		line.append(result);
	}
}