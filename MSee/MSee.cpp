#include "MSee.h"
#include <thread>
#include <assert.h>

#include <Poco/Dynamic/Var.h>

#define SWITH_CHANNEL_NOTIFICATION_TOKEN std::string("SwitchChannelNotification")

MSee::MSee(int argc, char**argv, std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName)
{
	config = new Config(instanceName, configFileName);
	MSee::streamer = new Streamer(argc,argv,*config);
	MSee::streamer->initialize();
	MSee::channelCount = MSee::streamer->countChannels();
	
}

void MSee::start(){
	MSee::streamer->play();
}
void MSee::stop(){
	MSee::streamer->stop();
}
void MSee::switchTo(int channelId){
	
	MSee::streamer->setChannel(channelId);
	printf("channel now set to %d\n",channelId);
}

int MSee::getChannelCount(){
	return MSee::streamer->countChannels();
}

Streamer* MSee::streamer = NULL;
unsigned char MSee::currentChannel = 0;
unsigned char MSee::channelCount = 0;


void handle_message(const std::string & message)
{
    printf("ws received>>> %s\n", message.c_str());
	Poco::JSON::Parser parser;
	parser.parse(message);
	
	Poco::JSON::Object::Ptr object = parser.result().extract<Poco::JSON::Object::Ptr>();
	std::string type = object->get(std::string("eventType")).convert<std::string>();
	if(type == SWITH_CHANNEL_NOTIFICATION_TOKEN){
		printf("switching channels ... \n");
		MSee::currentChannel ++;
		MSee::currentChannel = MSee::currentChannel%MSee::channelCount;
		MSee::switchTo(MSee::currentChannel);		
	}
}


void handleCommunications(MSee * msee){
	easywsclient::WebSocket::pointer ws;
	ws = easywsclient::WebSocket::from_url(msee->getRobotURI());
	assert(ws);
	std::string message = "{\"type\":\"remoteIdentification\", \"id\":\"tegra\"}";
    ws->send(message);
	printf("sent \"%s\"\n",message.c_str());
    bool done = false;
    while(!done){
    	        ws->poll();
    	        ws->dispatch(handle_message);
    }
    delete ws; //
}

void MSee::robotDiscovered(std::string& uri){
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
