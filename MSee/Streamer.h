#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include <gst/gst.h>
#include "Config.h"
#include "Source.h"

class Streamer
{
private:
	int argc;
	char ** argv;
	Config config;
	std::vector<GstPad*> channels;
	GstElement *pipeline;
	GstBus *bus;
	bool stopped=false;
	void createPipeline();
public:
	Streamer(int, char**,Config&);
	void initialize();
	std::string getPipelineDefinition();
	int countChannels();
	std::vector<std::string> getChannelNames();
	void free();
	void play();
	void stop();
	bool done();
	void setChannel(int channelId);
};

