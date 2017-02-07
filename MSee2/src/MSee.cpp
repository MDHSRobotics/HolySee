#include "MSee.h"


MSee::MSee(std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName)
{
	config = new Config(instanceName, configFileName);
	streamer = new Streamer(0,NULL,*config);
	streamer->initialize();
}

void MSee::start(){
	streamer->play();
}
void MSee::stop(){
	streamer->stop();
}
void MSee::switchTo(int channelId){
	streamer->setChannel(channelId);
}
int MSee::getChannelCount(){
	return streamer->countChannels();
}
