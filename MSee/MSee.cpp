#include "MSee.h"
#include <thread>
#include <assert.h>
#include "Streamer.h"

#include <Poco/Dynamic/Var.h>

#define SWITH_CHANNEL_NOTIFICATION_TOKEN std::string("SwitchChannelNotification")
#define CONSOLE_CONNECTION_NOTIFICATION_TOKEN std::string("ConsoleConnectionNotification")

MSee::MSee(int argc, char**argv, std::string& instanceName, std::string& configFileName) : instanceName(instanceName), configFileName(configFileName) 
{
	config = new Config(instanceName, configFileName);
	MSee::streamer = new Streamer(argc,argv,*config, this);
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information("MSee instantiated");
}

MSee::~MSee(){
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.close();
}

void MSee::start(){
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information("starting streamer");
	MSee::streamer->play();
}


void MSee::stop(){
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information("stopping streamer");
	MSee::streamer->stop();
}
void MSee::switchTo(int channelId){
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information("switching channel");
	MSee::streamer->setChannel(channelId);
	//printf("channel now set to %d\n",channelId);
}

int MSee::getChannelCount(){
	//printf("streamer has %d channels\n",MSee::streamer->countChannels());
	return MSee::streamer->countChannels();
}

Streamer* MSee::streamer = NULL;
unsigned char MSee::currentChannel = 0;
unsigned char MSee::channelCount = 0;


void handle_message(const std::string & message)
{
    std::string logmessage("");
    logmessage.append("ws received>>> ");
    logmessage.append(message);
    logmessage.append("\n");
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information(logmessage.c_str());

	Poco::JSON::Parser parser;
	parser.parse(message);
	Poco::JSON::Object::Ptr object = parser.result().extract<Poco::JSON::Object::Ptr>();

	if(object->has(std::string("eventType"))){
		std::string type = object->get(std::string("eventType")).convert<std::string>();
		if(type == SWITH_CHANNEL_NOTIFICATION_TOKEN){
			//printf("switching channels ... \n");
			MSee::currentChannel ++;
			MSee::currentChannel = MSee::currentChannel%MSee::channelCount;
			MSee::switchTo(MSee::currentChannel);		
		}
		else if(type == CONSOLE_CONNECTION_NOTIFICATION_TOKEN){
            //printf("getting console connection infomration: \n");
			//printf("\t%s\n",message.c_str());
			if(object->has(std::string("consoleAddress")))
			{
				std::string address = object->get(std::string("consoleAddress")).convert<std::string>();
				MSee::streamer->setConsole(address);	
			}
		}
	}
}


void handleCommunications(MSee * msee){
	easywsclient::WebSocket::pointer ws;
	ws = easywsclient::WebSocket::from_url(msee->getRobotURI());
	assert(ws);
    std::string logmessage;
    logmessage.append(std::string("connected to >>> "));
    logmessage.append(msee->getRobotURI());
    logmessage.append(std::string("\n"));
    Poco::Logger& logger = Poco::Logger::get("MSeeLogger");
    logger.information(logmessage.c_str());
	std::string message = "{\"type\":\"remoteIdentification\", \"id\":\"tegra\"}";
	msee->post(message);
    bool done = false;
    logmessage.clear();
    while(!done){
        easywsclient::WebSocket::readyStateValues state = ws->getReadyState();
        switch(state){
            case easywsclient::WebSocket::readyStateValues::CLOSING:
                logmessage = std::string("ws closing");
                logger.information(logmessage.c_str());
            break;
            case easywsclient::WebSocket::readyStateValues::CLOSED:
                logmessage = std::string("ws closed");
                logger.information(logmessage.c_str());
            break;
            case easywsclient::WebSocket::readyStateValues::CONNECTING:
                logmessage = std::string("ws connecting");
                logger.information(logmessage.c_str());
            break;
            case easywsclient::WebSocket::readyStateValues::OPEN:
                logmessage = std::string("ws still opened");
                logger.information(logmessage.c_str());
                ws->poll(50);
                ws->dispatch(handle_message);
                while(msee->hasMessages()){
                    const std::string& messageSent = msee->nextMessage(); 
                    ws->send(messageSent);
                    printf("sent \"%s\"\n",messageSent.c_str());
                }
            break;
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
	//printf("queueing \"%s\"\n",message.c_str());
}

bool MSee::hasMessages(){
	return !outqueue.empty();
}

std::string MSee::nextMessage(){
	std::string message = outqueue.front();
	outqueue.pop();
	return message;
}
