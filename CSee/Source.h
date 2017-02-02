#pragma once
#include <string>
#include <vector>

class Source
{
protected:
	std::string name;
	std::string arName;  //filter name to use for augmented reality view
	std::string cvName;  //filter name to use for CV app sink
	bool _showRaw = false;
	std::vector<std::string> connectionNames; // a pipeline connection means that a source is streaming something into some part of the pipeline
	std::vector<std::string> channelNames; // a channel is a connection that is intended to be streamed out, not all connections are streamed out (e.g. app sinks)
public:
	Source(std::string& name, bool showRaw, std::string& AR_Name, std::string& CV_Name);
	~Source();
	std::string getName();
	std::string Source::getARName();
	std::string Source::getCVName();
	bool Source::showRaw();
	bool Source::hasAR();
	bool Source::hasCV();
	int Source::countConnections();
	int Source::countChannels();
	std::vector< std::string> getChannelNames();
	std::vector<std::string> getConnectionNames();
	virtual std::string getPipelineSegment() = 0; //abstract method must be implemented by subclasses
};

