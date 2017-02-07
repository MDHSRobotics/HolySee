#pragma once
#include <string>
#include <vector>
#include <memory>
#include <gst/gst.h>
#include "Source.h"

class Streamer
{
private:
	int argc;
	char ** argv;
	std::string pipelineDefinition;
	std::vector<std::shared_ptr<Source>> sources;
	std::vector<std::string> channelNames;
	std::vector<GstPad*> channels;
	GstElement *pipeline;
	GstBus *bus;
	bool stopped=false;
public:
	Streamer(int, char**);
	void initialize();
	std::string getPipelineDefinition();
	bool registerSource(std::shared_ptr<Source>&);
	int countChannels();
	std::vector<std::string> getChannelNames();
	void free();
	void play();
	void stop();
	bool done();
	void setChannel(int channelId);
};

