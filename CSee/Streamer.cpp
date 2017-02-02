#include "stdafx.h"
#include "Streamer.h"
#include <stdio.h>


Streamer::Streamer()
{
}

void Streamer::initialize(){
	printf("streamer has %d sources\n", this->sources.size());
	int channelIndex = 1;
	for (int i = 0; i < this->sources.size(); i++){
		Source* source = sources[i].get();
		if (source->countChannels()>0){
			printf("source %s has %d connections and %d channels.\n", source->getName().c_str(), source->countConnections(), source->countChannels());
			for (int c = 0; c < source->getChannelNames().size(); c++){
				std::string channelName = std::string(std::to_string(channelIndex) + "." + (source->getChannelNames()[c]));
				this->channelNames.push_back(channelName);
				channelIndex++;
			}
		}
	}
	printf("streamer has: %d channels\n", this->countChannels());
	for (int i = 0; i < this->countChannels(); i++){
		printf("channel: %s\n", this->channelNames[i].c_str());
	}

	printf("pipeline:\n\t%s\n", getPipeline().c_str());
	printf("%s\n", "Streamer initialized");
}


bool Streamer::registerSource(std::shared_ptr<Source> source){
	sources.push_back(source);
	printf("%s registered\n",source->getName().c_str());
	return true; //invalid registration
}

int Streamer::countChannels(){
	return channelNames.size();
}

void Streamer::free(){
	//free resources
	printf("%s\n","free resources");
	if (sources.size() > 0){
		sources.clear();
	}
}

std::string Streamer::getPipeline(){
	std::string pipeline;
	std::string streamName("stream");

	//start by defining the end of the pipeline
	if (this->countChannels() > 1){
		pipeline.append("input-selector name=");
		pipeline.append(streamName);
		pipeline.append(" ! autovideosink "); //include the trailing space to create a separator that we know we will need
	}
	else if (this->countChannels() > 0){
		pipeline.append("autovideosink name="); //include the trailing space to create a separator that we know we will need
		pipeline.append(streamName);
		pipeline.append(" ");
	}

	//next add the definition to each source.  they will need to tie into the specified output, which in our case is called stream
	for (int s = 0; s < this->sources.size(); s++){
		Source* source = sources.at(s).get();
		if (source->countConnections()>0){
			//source will need to be added to pipeline
			std::string& base = source->getPipelineSegment();
			if (source->countConnections() > 1){
				//tee needed
				pipeline.append(base);
				pipeline.append(" ! ");
				pipeline.append("tee name=");
				pipeline.append(source->getName());
				pipeline.append(" ");
				for (int c = 0; c<source->countChannels(); c++){
					pipeline.append(source->getName());
					pipeline.append(". ! queue ! ");
					pipeline.append(streamName);
					pipeline.append(". ");
				}
			}
			else if (source->countConnections() > 0){
				pipeline.append(base);
				pipeline.append(" ! ");
				pipeline.append(streamName);
				pipeline.append(". ");
			}
		}
	}


	return pipeline;
}