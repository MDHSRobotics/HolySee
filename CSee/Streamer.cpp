#include "Streamer.h"
#include <stdio.h>
#include <thread>

Streamer::Streamer(int argc, char** argv) : argc(argc), argv(argv)
{
}

void Streamer::stop(){
	stopped = true;
}
bool Streamer::done(){
	return stopped;
}

void processKeys( Streamer*  handler){
	 printf("%s\n","Press spacebar to switch channels or X key to exit ..." );

	  // Set terminal to raw mode
	  system("stty raw");

	  // Wait for single character
	  char ch = getchar();

	  while(ch!='x'){
		  if(ch == ' '){
				 printf("%s\n","switching channels..." );
		  }
	  }
	 printf("%s\n","exiting..." );

	  // Reset terminal to normal "cooked" mode
	  system("stty cooked");

}

void Streamer::play(){
	/* start playing */
	gst_element_set_state(pipeline,GST_STATE_PLAYING);
	//play until interrupted
	//error or eos will end the pipeline
	GstMessage* msg;
	bool done = false;
	bus = gst_element_get_bus(pipeline);

	//start a keyboard listener
	Streamer * handler = this;
	std::thread keyboardListener(processKeys,handler);
	keyboardListener.join();

	while(bus!=NULL && !done && !stopped){
		msg = gst_bus_timed_pop_filtered(bus,200,(GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_ANY));  //TODO: refactor remove message any
		if(msg != NULL){
			printf("message received: 0x%08x: ",msg->type);
			if(msg->type == GST_MESSAGE_ERROR){
				 printf("%s\n","bus sent an error message" );
			}
			else if(msg->type == GST_MESSAGE_EOS){
				 printf("%s\n","bus sent an EOS message" );
			}
			else{
				 printf("%s\n","bus sent some other message" );
			}
			gst_message_unref(msg);
		}
	}
	free();
}

void Streamer::setChannel(int channelId){
	 printf("setting channel to %d\n",channelId );
	 //TODO: implement
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

	printf("pipeline:\n\t%s\n", getPipelineDefinition().c_str());

	//initialize gstreamer
	gst_init(&argc,&argv);

	/* build the pipeline */
	GError* error =  NULL;
	pipeline = gst_parse_launch(pipelineDefinition.c_str(),&error);
	if(pipeline ==NULL || error !=NULL){
		printf("Parse error %s\n",error->message);
	}

	//map channels to our channel dictionary
	GstElement* switchEl = gst_bin_get_by_name((GstBin*)pipeline,"stream");
	if(switchEl!=NULL){
		printf("switch element has %d input pads\n",switchEl->numsinkpads);
		int i=0;
		GstIterator* iter = gst_element_iterate_sink_pads(switchEl);
		GValue vPad = G_VALUE_INIT;
		channelNames.clear();  //TODO: refactor - do I need channelNames populated before here?
		while(gst_iterator_next(iter,&vPad)==GST_ITERATOR_OK){
			GstPad* pad = GST_PAD(g_value_get_object(&vPad));
			const gchar* pad_name = gst_pad_get_name(pad);
			printf("padName: %s\n",pad_name);
			channelNames[i]=std::string(pad_name);
			channels[i]=pad;
			g_free(const_cast<gchar*>(pad_name));
			i++;
		}
		gst_iterator_free(iter);
	}

	for(int c=0;c<channels.size();c++){
		printf("channel %s %s\n", channelNames[c].c_str(),(channels[c]!=NULL?" is defined":" is NULL"));
	}
	printf("%s\n", "Streamer initialized");

}


bool Streamer::registerSource(std::shared_ptr<Source>& source){
	sources.push_back(source);
	printf("%s registered\n",source->getName().c_str());
	return true; //invalid registration
}

int Streamer::countChannels(){
	return channelNames.size();
}

std::vector<std::string> Streamer::getChannelNames(){
	return channelNames;
}

void Streamer::free(){
	//free resources
	if (sources.size() > 0){
		sources.clear();
	}

	gst_object_unref(bus);
	gst_element_set_state(pipeline,GST_STATE_NULL);
	gst_object_unref(pipeline);
	printf("%s\n","resources freed");
}

std::string Streamer::getPipelineDefinition(){
	std::string streamName("stream");

	//start by defining the end of the pipeline
	if (this->countChannels() > 1){
		pipelineDefinition.append("input-selector name=");
		pipelineDefinition.append(streamName);
		pipelineDefinition.append(" ! autovideosink "); //include the trailing space to create a separator that we know we will need
	}
	else if (this->countChannels() > 0){
		pipelineDefinition.append("autovideosink name="); //include the trailing space to create a separator that we know we will need
		pipelineDefinition.append(streamName);
		pipelineDefinition.append(" ");
	}

	//next add the definition to each source.  they will need to tie into the specified output, which in our case is called stream
	for (int s = 0; s < this->sources.size(); s++){
		Source* source = sources.at(s).get();
		if (source->countConnections()>0){
			//source will need to be added to pipeline
			std::string base = source->getPipelineSegment();
			if (source->countConnections() > 1){
				//tee needed
				pipelineDefinition.append(base);
				pipelineDefinition.append(" ! ");
				pipelineDefinition.append("tee name=");
				pipelineDefinition.append(source->getName());
				pipelineDefinition.append(" ");
				for (int c = 0; c<source->countChannels(); c++){
					pipelineDefinition.append(source->getName());
					pipelineDefinition.append(". ! queue ! ");
					pipelineDefinition.append(streamName);
					pipelineDefinition.append(". ");
				}
			}
			else if (source->countConnections() > 0){
				pipelineDefinition.append(base);
				pipelineDefinition.append(" ! ");
				pipelineDefinition.append(streamName);
				pipelineDefinition.append(". ");
			}
		}
	}


	return pipelineDefinition	;
}
