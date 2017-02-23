#include "Streamer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Streamer::Streamer(int argc, char** argv,Config& config) : argc(argc), argv(argv),config(config)
{
}

void Streamer::stop(){
	stopped = true;
}
bool Streamer::done(){
	return stopped;
}


void Streamer::play(){
	 printf("%s\n","playing" );
	/* start playing */
	gst_element_set_state(pipeline,GST_STATE_PLAYING);
	//play until interrupted
	//error or eos will end the pipeline
	GstMessage* msg;
	bool done = false;
	bus = gst_element_get_bus(pipeline);



	while(bus!=NULL && !done && !stopped){
		msg = gst_bus_timed_pop_filtered(bus,200,(GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_ANY));  //TODO: refactor remove message any
		if(msg != NULL){
			//printf("message received: 0x%08x:\n ",msg->type);
			if(msg->type == GST_MESSAGE_ERROR){
				 printf("%s\n","bus sent an error message" );
			}
			else if(msg->type == GST_MESSAGE_EOS){
				 printf("%s\n","bus sent an EOS message" );
			}
			else{
				 //printf("%s\n","bus sent some other message" );
			}
			gst_message_unref(msg);
		}
	}
	free();
}

void Streamer::setChannel(int channelId){
	 printf("setting channel to %d\n",channelId );
	 std::string desiredChannel = std::string("sink_")+std::to_string(channelId);
		GstElement* switchEl = gst_bin_get_by_name((GstBin*)pipeline,"stream");
		if(switchEl!=NULL){
			printf("found switchEL\n");
			//GstPad* pad = channels.at(channelId);
			//g_object_set(G_OBJECT(switchEl),"active-pad",pad,NULL);
			GstIterator* iter = gst_element_iterate_sink_pads(switchEl);
			GValue vPad = G_VALUE_INIT;
			while(gst_iterator_next(iter,&vPad)==GST_ITERATOR_OK){
				GstPad* pad = GST_PAD(g_value_get_object(&vPad));
				const gchar* _pad_name = gst_pad_get_name(pad);
				std::string pad_name ( _pad_name);
				printf("padName: %s, desired %s\n",pad_name.c_str(),desiredChannel.c_str());
				if(pad_name==desiredChannel){
					printf("found the pad I want...\n");
					g_object_set(G_OBJECT(switchEl),"active-pad",pad,NULL);
				}
				g_free(const_cast<gchar*>(_pad_name));
			}
		}
}



void Streamer::initialize(){
	std::vector<std::string> channelNames;

	//initialize gstreamer
	gst_init(&argc,&argv);

	/* build the pipeline */
	GError* error =  NULL;
	pipeline = gst_parse_launch(config.getPipelineDefinition().c_str(),&error);

	if(pipeline ==NULL || error !=NULL){
		printf("Parse error %s\n",error->message);
		exit(0);
	}

	//map channels to our channel dictionary
	try{
	GstElement* switchEl = gst_bin_get_by_name((GstBin*)pipeline,"stream");
	if(switchEl!=NULL){
		printf("switch element has %d input pads\n",switchEl->numsinkpads);
		int i=0;
		GstIterator* iter = gst_element_iterate_sink_pads(switchEl);
		GValue vPad = G_VALUE_INIT;
		channelNames.clear();
		while(gst_iterator_next(iter,&vPad)==GST_ITERATOR_OK){
			GstPad* pad = GST_PAD(g_value_get_object(&vPad));
			const gchar* pad_name = gst_pad_get_name(pad);
			channelNames.push_back(std::string(pad_name));
    		channels.push_back(pad);
			printf("padName: %s\n",pad_name);
			g_free(const_cast<gchar*>(pad_name));
			i++;
		}
		gst_iterator_free(iter);
	}
	printf("%s\n", "Streamer initialized");
	for(int c=0;c<channels.size();c++){
		printf("channel %s %s\n", channelNames[c].c_str(),(channels[c]!=NULL?" is defined":" is NULL"));
	}
	}
	catch(std::exception e){
		printf("ERROR: %s\n",e.what());
	}
	printf("%s\n", "Streamer initialized");

}

void Streamer::free(){
	//free resources
	//TODO:  refactor to free resources in config
//	if (sources.size() > 0){
//		sources.clear();
//	}

	gst_object_unref(bus);
	gst_element_set_state(pipeline,GST_STATE_NULL);
	gst_object_unref(pipeline);
	printf("%s\n","resources freed");
}

int Streamer::countChannels(){
	return channels.size();
}
