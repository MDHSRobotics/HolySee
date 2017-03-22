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

void Filter::postBooleanEvent(std::string eventName, bool eventData){
	GstStructure* msgStruct = gst_structure_new(eventName.c_str(), "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_BOOLEAN, eventData, NULL);
	post(msgStruct);
}

void Filter::postStringEvent(std::string eventName, std::string eventData){
	GstStructure* msgStruct = gst_structure_new(eventName.c_str(), "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_STRING, eventData.c_str(), NULL);
	post(msgStruct);
}

void Filter::postIntEvent(std::string eventName, int eventData){
	GstStructure* msgStruct = gst_structure_new(eventName.c_str(), "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_INT, eventData, NULL);
	post(msgStruct);
}

void Filter::postDoubleEvent(std::string eventName, double eventData){
	GstStructure* msgStruct = gst_structure_new(eventName.c_str(), "filter", G_TYPE_STRING, getName().c_str(), "eventData", G_TYPE_DOUBLE, eventData, NULL);
	post(msgStruct);
}

void Filter::setParameters(std::string& parameters){
	this->parameters = parameters;
}

std::string Filter::getParameters(){
	return parameters;
}
