#include "MSee.h"
#include <thread>
#include <assert.h>
#include "Streamer.h"

#include <Poco/Dynamic/Var.h>

#define SWITH_CHANNEL_NOTIFICATION_TOKEN std::string("SwitchChannelNotification")

MSee::MSee(int argc, char**argv, std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName)
{
	config = new Config(instanceName, configFileName);
	MSee::streamer = new Streamer(argc,argv,*config, this);
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
	msee->post(message);
    bool done = false;
    while(!done){
    	        ws->poll(50);
    	        ws->dispatch(handle_message);
				while(msee->hasMessages()){
					const std::string& messageSent = msee->nextMessage(); 
					ws->send(messageSent);
					printf("sent \"%s\"\n",messageSent.c_str());
				}

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

void MSee::targetAcquiredUpdate(std::string filter, bool targetAcquired){
	std::string message = "{\"type\":\"targetAcquiredNotification\", \"filter\":\"";
	message.append(filter);
	message.append("\", \"targetAcquired\":");
	message.append((targetAcquired?"true":"false"));
	message.append("}");
    post(message);
}

void MSee::post(std::string message){
	outqueue.push(message);
	printf("queueing \"%s\"\n",message.c_str());
}

bool MSee::hasMessages(){
	return !outqueue.empty();
}

std::string MSee::nextMessage(){
	std::string message = outqueue.front();
	outqueue.pop();
	return message;
}
