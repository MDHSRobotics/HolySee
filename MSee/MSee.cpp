#include "MSee.h"
#include <thread>
#include <assert.h>

MSee::MSee(int argc, char**argv, std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName)
{
	config = new Config(instanceName, configFileName);
	streamer = new Streamer(argc,argv,*config);
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

void handle_message(const std::string & message)
{
    printf("ws received>>> %s\n", message.c_str());
}

void handleCommunications(MSee * msee){
	easywsclient::WebSocket::pointer ws;
	ws = easywsclient::WebSocket::from_url(msee->getRobotURI());
	assert(ws);
	std::string message = "{\"type\":\"remoteIdentification\", \"id\":\"tegra\"}";
    ws->send(message);
    bool done = false;
    while(!done){
    	        ws->poll();
    	        ws->dispatch(handle_message);
    }
    delete ws; //
}

void MSee::robotDIscovered(std::string& uri){
	setRobotURI(uri);
	//start ws_client thread
	std::thread client(handleCommunications,this);
	client.detach();
}

std::string& MSee::getRobotURI(){
	return robotURI;
}

void MSee::setRobotURI(std::string& uri){
	robotURI = uri;
}
