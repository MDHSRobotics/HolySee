/*
* GStreamer
* Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
* Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
* Copyright (C) 2017 RoboticsLinux <<user@hostname.org>>
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*
* Alternatively, the contents of this file may be used under the
* GNU Lesser General Public License Version 2.1 (the "LGPL"), in
* which case the following provisions apply instead of the ones
* mentioned above:
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
*/

/**
* SECTION:element-arfilter
*
* FIXME:Describe arfilter here.
*
* <refsect2>
* <title>Example launch line</title>
* |[
* gst-launch -v -m fakesrc ! arfilter ! fakesink silent=TRUE
* ]|
* </refsect2>
*/
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/core/types_c.h"
#include <gst/gstelement.h>
#include <gst/app/gstappsink.h>



#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gst/gst.h>

#include "gstarfilter.h"
#include "FilterManager.h"

GST_DEBUG_CATEGORY_STATIC(gst_ar_filter_debug);
#define GST_CAT_DEFAULT gst_ar_filter_debug

/* Filter signals and args */
enum
{
	/* FILL ME */
	LAST_SIGNAL
};

enum
{
	PROP_0,
	PROP_SILENT,
	PROP_FILTER
};

/* the capabilities of the inputs and outputs.
*
* describe the real formats here.
*/
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE("sink",
	GST_PAD_SINK,
	GST_PAD_ALWAYS,
	GST_STATIC_CAPS("ANY")
	);

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE("src",
	GST_PAD_SRC,
	GST_PAD_ALWAYS,
	GST_STATIC_CAPS("ANY")
	);

#define gst_ar_filter_parent_class parent_class
G_DEFINE_TYPE(GstArFilter, gst_ar_filter, GST_TYPE_ELEMENT);

static void gst_ar_filter_set_property(GObject * object, guint prop_id,
	const GValue * value, GParamSpec * pspec);
static void gst_ar_filter_get_property(GObject * object, guint prop_id,
	GValue * value, GParamSpec * pspec);

static gboolean gst_ar_filter_sink_event(GstPad * pad, GstObject * parent, GstEvent * event);
static GstFlowReturn gst_ar_filter_chain(GstPad * pad, GstObject * parent, GstBuffer * buf);
static void gst_ar_filter_stop_processing(GstObject * parent);

static gboolean gst_ar_filter_src_query(GstPad    *pad,
	GstObject *parent,
	GstQuery  *query);


/* GObject vmethod implementations */

/* initialize the arfilter's class */
static void
gst_ar_filter_class_init(GstArFilterClass * klass)
{
//	printf("%s\n", "gst_ar_filter_class_init");

	GObjectClass *gobject_class;
	GstElementClass *gstelement_class;

	gobject_class = (GObjectClass *)klass;
	gstelement_class = (GstElementClass *)klass;

	gobject_class->set_property = gst_ar_filter_set_property;
	gobject_class->get_property = gst_ar_filter_get_property;

	g_object_class_install_property(gobject_class, PROP_SILENT,
		g_param_spec_boolean("silent", "Silent", "Produce verbose output ?",
		FALSE, (GParamFlags)G_PARAM_READWRITE));

	g_object_class_install_property(gobject_class, PROP_FILTER,
		g_param_spec_string("filter", "Filter", "Specify filter to apply",
		NULL, (GParamFlags)G_PARAM_READWRITE));

	gst_element_class_set_details_simple(gstelement_class,
		"ArFilter - an OpenCV filter plugin",
		"FIXME:Generic",
		"FIXME:Generic Template Element",
		"Maritn Smith <<msmith92663@gmail.com>>");

	gst_element_class_add_pad_template(gstelement_class,
		gst_static_pad_template_get(&src_factory));
	gst_element_class_add_pad_template(gstelement_class,
		gst_static_pad_template_get(&sink_factory));
}

static void arfilter_post(GstArFilter * filter,std::string& message){
	GstMessage * gstMessage;
	gstMessage = gst_message_new_application(GST_OBJECT(filter),
			gst_structure_new(message.c_str(), NULL));
	gst_element_post_message (GST_ELEMENT(filter),gstMessage);
}

/* initialize the new element
* instantiate pads and add them to element
* set pad calback functions
* initialize instance structure
*/
static void
gst_ar_filter_init(GstArFilter * filter)
{
//	printf("%s\n", "gst_ar_filter_init");

	filter->sinkpad = gst_pad_new_from_static_template(&sink_factory, "sink");
	gst_pad_set_event_function(filter->sinkpad,
		GST_DEBUG_FUNCPTR(gst_ar_filter_sink_event));
	gst_pad_set_chain_function(filter->sinkpad,
		GST_DEBUG_FUNCPTR(gst_ar_filter_chain));
	//gst_pad_set_query_function(filter->sinkpad,
	//	gst_ar_filter_src_query);
	GST_PAD_SET_PROXY_CAPS(filter->sinkpad);
	gst_element_add_pad(GST_ELEMENT(filter), filter->sinkpad);

	filter->srcpad = gst_pad_new_from_static_template(&src_factory, "src");
	GST_PAD_SET_PROXY_CAPS(filter->srcpad);
	gst_element_add_pad(GST_ELEMENT(filter), filter->srcpad);

	filter->silent = FALSE;


}

static void
gst_ar_filter_set_property(GObject * object, guint prop_id,
const GValue * value, GParamSpec * pspec)
{
	GstArFilter *filter = GST_ARFILTER(object);

	switch (prop_id) {
	case PROP_SILENT:
		filter->silent = g_value_get_boolean(value);
		break;
	case PROP_FILTER:{
		/* load correct filter
		*/
		filter->filterName = g_string_new(g_value_get_string(value));  //gives us the filter name
		//printf("filter: %s\n", filter->filterName->str);



		std::string fName(filter->filterName->str);
		if (FilterManager::getInstance().contains(fName)){
			//printf("have a match for: %s\n", filter->filterName->str);
			//load the right filter implementation
			filter->pFilter = FilterManager::getInstance().get(fName);
		}
	}
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
gst_ar_filter_get_property(GObject * object, guint prop_id,
GValue * value, GParamSpec * pspec)
{
	GstArFilter *filter = GST_ARFILTER(object);

	switch (prop_id) {
	case PROP_SILENT:
		g_value_set_boolean(value, filter->silent);
		break;
	case PROP_FILTER:
		g_value_set_string(value, filter->filterName->str);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

GString * FIELD_WIDTH_TOKEN = g_string_new("width");
GString * FIELD_HEIGHT_TOKEN = g_string_new("height");
GString * FIELD_FORMAT_TOKEN = g_string_new("format");

gboolean
inspectField(GQuark field_id,
const GValue *value,
gpointer user_data){
	GstArFilter *filter = (GstArFilter *)user_data;

	GString * fieldName = g_string_new(g_quark_to_string(field_id));
	GString * fieldValue = g_string_new(gst_value_serialize(value));

	if (g_strcmp0(fieldName->str,FIELD_WIDTH_TOKEN->str)    == 0){
		filter->width = atoi(fieldValue->str);
	}
	else if (g_strcmp0(fieldName->str,FIELD_HEIGHT_TOKEN->str)    == 0){
		filter->height = atoi(fieldValue->str);
	}
	else if (g_strcmp0(fieldName->str,FIELD_FORMAT_TOKEN->str)    == 0){
		filter->format = fieldValue;
	}
	return true;
}

/* GstElement vmethod implementations */

/* this function handles sink events */
static gboolean
gst_ar_filter_sink_event(GstPad * pad, GstObject * parent, GstEvent * event)
{
	GstArFilter *filter;
	gboolean ret;

	filter = GST_ARFILTER(parent);

	GST_LOG_OBJECT(filter, "Received %s event: %" GST_PTR_FORMAT,
		GST_EVENT_TYPE_NAME(event), event);

	switch (GST_EVENT_TYPE(event)) {
	case GST_EVENT_CAPS:
	{
		GstCaps * caps;
		gst_event_parse_caps(event, &caps);
		int width, height, framerate, format;
		gboolean ret;
		GstStructure *structure;
		structure = gst_caps_get_structure(caps, 0);

		//detects width, height and pixel format
		gst_structure_foreach(structure, inspectField, filter);
		/* and forward */
		ret = gst_pad_push_event(filter->srcpad, event);
		break;
	}
	case GST_EVENT_EOS:
		gst_ar_filter_stop_processing(parent);
		ret = gst_pad_event_default(pad, parent, event);
		break;
	case GST_EVENT_STREAM_START:
		//printf("steam start event ... \n");
		if (filter->filterName != NULL && filter->filterName->len > 0){
			GstBus *bus = GST_ELEMENT_BUS(filter);
			filter->pFilter->setBus(bus);
			GstStructure *structure = gst_structure_new("initevent", "element", G_TYPE_STRING, "arfilter", "filter", G_TYPE_STRING, filter->filterName->str, NULL);
			GstMessage *msg = gst_message_new_application(GST_OBJECT(filter), structure);
			gst_bus_post(bus, msg);
		}
		break;			
	default:
		ret = gst_pad_event_default(pad, parent, event);
		break;
	}
	return ret;
}

bool announced = false;

/* chain function
* this function does the actual processing
*/
static GstFlowReturn
gst_ar_filter_chain(GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
	GstArFilter *filter;
	filter = GST_ARFILTER(parent);

	//// ---- Read frame and convert to opencv format ---------------
	if (filter->pFilter != NULL){
		//we have a filter implementation defined
		//use it to process the image


		//get a cv::Mat representation of the frame
		int bufferSize = gst_buffer_get_size(buffer);
		gst_buffer_is_writable(buffer);

		//check that we have the required info to build a valid CV::Mat of the frame
		if (filter->width > 0 && filter->height > 0 && bufferSize > 0 && filter->format->len > 0){
			int pixelSize = bufferSize / filter->width / filter->height;
			if (filter->silent == FALSE && !announced){
				announced = true;
				g_print("image[width:%d, height:%d, format:%s], buffer:%d, pixel depth:%d\n", filter->width, filter->height, filter->format->str, bufferSize, pixelSize);
			}
			GstMapInfo map;
			gst_buffer_map(buffer, &map, GST_MAP_READ);
			cv::Mat frame(cv::Size(filter->width, filter->height), CV_MAKETYPE(CV_8U, pixelSize), (char*)map.data, cv::Mat::AUTO_STEP);

			// we have the cv::Mat frame, now process it
			filter->pFilter->process(frame);

			gst_buffer_unmap(buffer, &map);
		}
	}
	/* just push out the incoming buffer without touching it */
	return gst_pad_push(filter->srcpad, buffer);
}

static void gst_ar_filter_stop_processing(GstObject * parent){
	printf("%s\n", "gst_ar_filter_stop_processing");
}



static gboolean
gst_ar_filter_src_query(GstPad* pad, GstObject* parent, GstQuery* query)
{
	gboolean ret;
	GstArFilter *filter;

	filter = GST_ARFILTER(parent);

	switch (GST_QUERY_TYPE(query)) {
	//case GST_QUERY_POSITION:
	//	/* we should report the current position */
	//	printf("position query\n");
	//	ret = gst_pad_query_default(pad, parent, query);
	//	break;
	//case GST_QUERY_DURATION:
	//	/* we should report the duration here */
	//	printf("duration query\n");
	//	ret = gst_pad_query_default(pad, parent, query);
	//	break;
	//case GST_QUERY_CAPS:
	//	/* we should report the supported caps here */
	//	printf("caps query\n");
	//	GstCaps * caps;
	//	gst_query_parse_caps(query, &caps);
	//	if (!GST_IS_CAPS(caps)){
	//		printf("caps is not a valid caps\n");
	//	}
	//	else{
	//		printf("caps size: %d\n", gst_caps_get_size(caps));
	//		for (int i = 0; i < gst_caps_get_size(caps); i++) {
	//			GstStructure *structure = gst_caps_get_structure(caps, i);
	//			char* fields;
	//			gst_structure_foreach(structure, inspectField,NULL);
	//			/*while (fields != NULL){
	//				printf("field: %s\n", fields);
	//				fields++;
	//			}*/
	//		}
	//	}
	//	ret = gst_pad_query_default(pad, parent, query);
	//	break;
	default:
		/* just call the default handler */
		printf("other query\n");
		ret = gst_pad_query_default(pad, parent, query);
		break;
	}
	return ret;
}

/* entry point to initialize the plug-in
* initialize the plug-in itself
* register the element factories and other features
*/
//static gboolean
//arfilter_init(GstPlugin * arfilter)
//{
//	printf("%s\n", "arfilter_init");
//	/* debug category for fltering log messages
//	*
//	* exchange the string 'Template arfilter' with your description
//	*/
//	GST_DEBUG_CATEGORY_INIT(gst_ar_filter_debug, "arfilter",
//		0, "Template arfilter");
//
//	return gst_element_register(arfilter, "arfilter", GST_RANK_NONE,
//		GST_TYPE_ARFILTER);
//}


/* PACKAGE: this is usually set by autotools depending on some _INIT macro
* in configure.ac and then written into and defined in config.h, but we can
* just set it ourselves here in case someone doesn't use autotools to
* compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
*/
//#ifndef PACKAGE
//#define PACKAGE "myfirstarfilter"
//#endif

/* gstreamer looks for this structure to register arfilters
*
* exchange the string 'Template arfilter' with your arfilter description
*/
//GST_PLUGIN_DEFINE(
//	GST_VERSION_MAJOR,
//	GST_VERSION_MINOR,
//	arfilter,
//	"Template arfilter",
//	arfilter_init,
//	VERSION,
//	"LGPL",
//	"GStreamer",
//	"http://gstreamer.net/"
//	)
