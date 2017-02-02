#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Source.h"

class Streamer
{
private:
	std::string pipeline;
	std::vector<std::shared_ptr<Source>> sources;
	std::vector<std::string> channelNames;
public:
	Streamer();
	void initialize();
	std::string getPipeline();
	bool registerSource(std::shared_ptr<Source>);
	int countChannels();
	void free();
};

