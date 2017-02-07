#ifndef __TEAM4141_MSEE_SOURCE__
#define __TEAM4141_MSEE_SOURCE__

#include <string>
#include <vector>

class Source
{
protected:
	std::string name;
	std::string device;
	std::string arName;  //filter name to use for augmented reality view
	std::string cvName;  //filter name to use for CV app sink
	bool _showRaw = false;
	std::vector<std::string> connectionNames; // a pipeline connection means that a source is streaming something into some part of the pipeline
	std::vector<std::string> channelNames; // a channel is a connection that is intended to be streamed out, not all connections are streamed out (e.g. app sinks)
public:
	Source(std::string name, std::string device, bool showRaw, std::string AR_Name, std::string CV_Name);
	~Source();
	std::string getName();
	std::string getDevice();
	std::string getARName();
	std::string getCVName();
	bool showRaw();
	bool hasAR();
	bool hasCV();
	int countConnections();
	int countChannels();
	std::vector< std::string> getChannelNames();
	std::vector<std::string> getConnectionNames();
	virtual std::string getPipelineSegment() = 0; //abstract method must be implemented by subclasses
};

#endif /* __TEAM4141_MSEE_SOURCE__ */
