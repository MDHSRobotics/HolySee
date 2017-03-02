#include "Filter.h"

Filter::Filter(std::string& name): name(name), bus(NULL)
{
}

std::string& Filter::getName(){
	return name;
}

void Filter::setBus(GstBus* bus){
	this->bus = bus;
}

void Filter::post(GstStructure * msgStruct){
	printf("posting something ...\n");

	GstMessage *msg = gst_message_new_application(GST_OBJECT(bus), msgStruct);
	gst_bus_post(bus, msg);
}
