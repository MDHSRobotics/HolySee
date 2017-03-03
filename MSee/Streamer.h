#ifndef __TEAM4141_STREAMER__
#define __TEAM4141_STREAMER__

#include <string>
#include <vector>
#include <memory>
#include <map>

#include <gst/gst.h>
#include "Config.h"
#include "Source.h"

class MSee;

class Streamer
{
private:
	int argc;
	char ** argv;
	Config config;
	std::vector<GstPad*> channels;
	GstElement *pipeline;
	GstBus *bus;
	MSee* msee;
	bool stopped=false;
	void createPipeline();
	std::string consoleAddress;
public:
	Streamer(int, char**,Config&, MSee* msee);
	void initialize();
	std::string getPipelineDefinition();
	int countChannels();
	std::vector<std::string> getChannelNames();
	void free();
	void play();
	void stop();
	bool done();
	void setChannel(int channelId);
	void setConsole(std::string address);
	bool isReady();
};

#endif /* __TEAM4141_STREAMER__ */
