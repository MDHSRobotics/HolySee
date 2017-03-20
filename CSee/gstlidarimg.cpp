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
* SECTION:element-lidarimg
*
* FIXME:Describe lidarimg here.
*
* <refsect2>
* <title>Example launch line</title>
* |[
* gst-launch-1.0 --gst-plugin-path=C:\projects\lidarsrc\x64\Release lidarsrc device=/dev/ttyUSB0 ! lidarimg ! video/x-raw, format=GRAY8, framerate=5/1, widht=640, height=480 ! videoconvert ! autovideosink
* ]|
* </refsect2>
*/
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/core/types_c.h"
#include <gst/gst.h>
#include "LidarDevice.h"

//#include <gst/gstelement.h>
//#include <gst/app/gstappsink.h>


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <cstdint>

template<int> struct BaseType { };
template<> struct BaseType<CV_8S>  { using base_type = int8_t; };
template<> struct BaseType<CV_8U>  { using base_type = uint8_t; };
template<> struct BaseType<CV_16S> { using base_type = int16_t; };
template<> struct BaseType<CV_16U> { using base_type = uint16_t; };
template<> struct BaseType<CV_32S> { using base_type = int32_t; };
template<> struct BaseType<CV_32F> { using base_type = float; };
template<> struct BaseType<CV_64F> { using base_type = double; };

#include "gstlidarimg.h"

GST_DEBUG_CATEGORY_STATIC(gst_lidar_img_debug);
#define GST_CAT_DEFAULT gst_lidar_img_debug

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
	PROP_WIDTH,
	PROP_HEIGHT,
	PROP_FORMAT
};

/* the capabilities of the inputs and outputs.
*
* describe the real formats here.
*/
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE("sink",
	GST_PAD_SINK,
	GST_PAD_ALWAYS,
	GST_STATIC_CAPS_ANY
	);

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE("src",
	GST_PAD_SRC,
	GST_PAD_ALWAYS,
	GST_STATIC_CAPS("video/x-raw, format=GRAY8, framerate=5/1")
	);

#define gst_lidar_img_parent_class parent_class
G_DEFINE_TYPE(GstLidarImg, gst_lidar_img, GST_TYPE_ELEMENT);

static void gst_lidar_img_set_property(GObject * object, guint prop_id,
	const GValue * value, GParamSpec * pspec);
static void gst_lidar_img_get_property(GObject * object, guint prop_id,
	GValue * value, GParamSpec * pspec);

static gboolean gst_lidar_img_sink_event(GstPad * pad, GstObject * parent, GstEvent * event);
static GstFlowReturn gst_lidar_img_chain(GstPad * pad, GstObject * parent, GstBuffer * buf);
static void gst_lidar_img_stop_processing(GstObject * parent);

static gboolean gst_lidar_img_src_query(GstPad    *pad,
	GstObject *parent,
	GstQuery  *query);


/* GObject vmethod implementations */

/* initialize the lidarimg's class */
static void
gst_lidar_img_class_init(GstLidarImgClass * klass)
{
	//g_print("%s\n", "gst_lidar_img_class_init");

	GObjectClass *gobject_class;
	GstElementClass *gstelement_class;

	gobject_class = (GObjectClass *)klass;
	gstelement_class = (GstElementClass *)klass;

	gobject_class->set_property = gst_lidar_img_set_property;
	gobject_class->get_property = gst_lidar_img_get_property;

	g_object_class_install_property(gobject_class, PROP_SILENT,
		g_param_spec_boolean("silent", "Silent", "Produce verbose output ?",
		FALSE, (GParamFlags)G_PARAM_READWRITE));

	g_object_class_install_property(gobject_class, PROP_WIDTH,
		g_param_spec_int("width", "Width", "Specify the width of the image to produce, default is 640",160,1280,640,(GParamFlags)G_PARAM_READWRITE));
	g_object_class_install_property(gobject_class, PROP_HEIGHT,
		g_param_spec_int("height", "Height", "Specify the height of the image to produce, default is 480", 160, 1280, 480, (GParamFlags)G_PARAM_READWRITE));

	gst_element_class_set_details_simple(gstelement_class,
		"LidarImg - an RP Lidar plugin",
		"FIXME:Generic",
		"FIXME:Generic Template Element",
		"Maritn Smith <<msmith92663@gmail.com>>");

	gst_element_class_add_pad_template(gstelement_class,
		gst_static_pad_template_get(&src_factory));
	gst_element_class_add_pad_template(gstelement_class,
		gst_static_pad_template_get(&sink_factory));

}

/* initialize the new element
* instantiate pads and add them to element
* set pad calback functions
* initialize instance structure
*/
static void
gst_lidar_img_init(GstLidarImg * filter)
{
	//g_print("%s\n", "gst_lidar_img_init");

	filter->sinkpad = gst_pad_new_from_static_template(&sink_factory, "sink");
	gst_pad_set_event_function(filter->sinkpad,
		GST_DEBUG_FUNCPTR(gst_lidar_img_sink_event));
	gst_pad_set_chain_function(filter->sinkpad,
		GST_DEBUG_FUNCPTR(gst_lidar_img_chain));
	gst_element_add_pad(GST_ELEMENT(filter), filter->sinkpad);

	filter->srcpad = gst_pad_new_from_static_template(&src_factory, "src");
	gst_pad_use_fixed_caps(filter->srcpad);

	gst_element_add_pad(GST_ELEMENT(filter), filter->srcpad);

	filter->silent = FALSE;
	filter->width = 640;
	filter->height = 480;
	//g_print("init done\n");
}

static void
gst_lidar_img_set_property(GObject * object, guint prop_id,
const GValue * value, GParamSpec * pspec)
{
	GstLidarImg *filter = GST_LIDARIMG(object);

	switch (prop_id) {
	case PROP_SILENT:
		filter->silent = g_value_get_boolean(value);
		break;
	case PROP_WIDTH:
		/* set the desired width		*/
		filter->width = g_value_get_int(value);  //gives us the width
		//g_print("width: %d\n", filter->width);
		break;
	case PROP_HEIGHT:
		/* set the desired width		*/
		filter->width = g_value_get_int(value);  //gives us the height
		//g_print("height: %d\n", filter->height);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
gst_lidar_img_get_property(GObject * object, guint prop_id,
GValue * value, GParamSpec * pspec)
{
	GstLidarImg *filter = GST_LIDARIMG(object);

	switch (prop_id) {
	case PROP_SILENT:
		g_value_set_boolean(value, filter->silent);
		break;
	case PROP_WIDTH:
		g_value_set_int(value, filter->width);
		break;
	case PROP_HEIGHT:
		g_value_set_int(value, filter->height);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

//std::string FIELD_WIDTH_TOKEN("width");
//std::string FIELD_HEIGHT_TOKEN("height");
//std::string FIELD_FORMAT_TOKEN("format");
//
//gboolean
//inspectField(GQuark field_id,
//const GValue *value,
//gpointer user_data){
//	GstLidarImg *filter = (GstLidarImg *)user_data;
//
//	std::string fieldName = std::string(g_quark_to_string(field_id));
//	std::string fieldValue = std::string(gst_value_serialize(value));
//
//	if (fieldName == "width"){
//		filter->width = std::stoi(fieldValue);
//	}
//	else if (fieldName == "height"){
//		filter->height = std::stoi(fieldValue);
//	}
//	else if (fieldName == "format"){
//		filter->format = fieldValue;
//	}
//	return true;
//}

/* GstElement vmethod implementations */

/* this function handles sink events */
static gboolean
gst_lidar_img_sink_event(GstPad * pad, GstObject * parent, GstEvent * event)
{
	GstLidarImg *filter;
	gboolean ret;

	filter = GST_LIDARIMG(parent);

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

		//						   gst_structure_foreach(structure, inspectField, filter);
						   
		/* and forward */
		ret = gst_pad_push_event(filter->srcpad, event);
		break;
	}
	case GST_EVENT_EOS:
		gst_lidar_img_stop_processing(parent);
		ret = gst_pad_event_default(pad, parent, event);
		break;
	default:
		ret = gst_pad_event_default(pad, parent, event);
		break;
	}
	return ret;
}

//bool announced = false;

/* chain function
* this function does the actual processing
*/
static GstFlowReturn
gst_lidar_img_chain(GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
//	g_print("gst_lidar_img_chain\n");
	GstLidarImg *filter;
	filter = GST_LIDARIMG(parent);

	GstCaps * caps = gst_caps_new_simple("video/x-raw",
		"format", G_TYPE_STRING, "GRAY8",
		"pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
		"width", G_TYPE_INT, filter->width,
		"height", G_TYPE_INT, filter->height,
		"framerate", GST_TYPE_FRACTION, 5, 1,
		NULL);
	if (!gst_pad_set_caps(pad, caps)) {
		GST_ELEMENT_ERROR(filter, CORE, NEGOTIATION, (NULL),
			("Some debug information here"));
		return GST_FLOW_ERROR;
	}
	int bufferSize = gst_buffer_get_size(buffer);
//	g_print("image[width:%d, height:%d, format:%s], buffer:%d\n", filter->width, filter->height, filter->format, bufferSize);

	GstMapInfo map;
	gst_buffer_map(buffer, &map, GST_MAP_READ);
//	g_print("data[size:%d]:\n", map.size);
//	for (int i = 0; i < map.size; i++){
//		guint8 byte = *(map.data + i);
//		g_print("%02x", byte);
//		if (i % 16 == 0) g_print("\n");
//		else if (i % 2 == 0) g_print(" ");
//	}
//	g_print("\n");
	int bytesRead = 0;
	int i = 0;
	Header header;
	unsigned char* data = reinterpret_cast<unsigned char*>(&(header));
	while (bytesRead < map.size && i < sizeof header){
		*(data + i) = *(map.data + bytesRead);
		i++;
		bytesRead++;
	}
//	g_print("header: bufferSize:%d, count:%d\n",header.size,header.count);
	double scale = (double)(filter->width < filter->height ? filter->width/2 : filter->height/2) / (double)LidarDevice::Range;
	int xOffset = (filter->width <= filter->height ? 0 : (filter->width-filter->height) / 2);
	int yOffset = (filter->width < filter->height ? (filter->height - filter->width) / 2 : 0);
//	g_print("width:%d, height:%d, range:%f, scale:%f\n", filter->width, filter->height, LidarDevice::Range, scale);
	cv::Mat frame(cv::Size(filter->width, filter->height), CV_MAKETYPE(CV_8U, 1), cv::Scalar(255));//creates an empty matrix that is intended to be grey scale with defined size
	
	int count = 0;
	while (bytesRead < map.size && count < header.count){
		i = 0;
		Reading reading;
		data = reinterpret_cast<unsigned char*>(&(reading));
		while (bytesRead < map.size && i < sizeof reading){
			*(data + i) = *(map.data + bytesRead);
			i++;
			bytesRead++;
		}
		//we have a re-constituted reading, now to plot it.  we need to convert the angle and distance into x & y & color
		double x = LidarDevice::calculateX(reading, scale, filter->width,xOffset);
		double y = LidarDevice::calculateY(reading,scale,filter->height,yOffset);
		unsigned char color = LidarDevice::calculateColor(reading);

		//if (count == 0){
			//show the first point for debugging purposes
			//g_print("reading:  angle:%f, distance:%f, quality:%02x, synch:%02x\n", reading.angle, reading.distance, reading.qualityFlag, reading.syncFlag);
		//	g_print("pixel:  x:%f, y:%f, color:%d\n", x, y, color);
		//}
		if (reading.qualityFlag != 0x00){
			//draw the point using the circle function to make it more visible
			cv::circle(frame, cv::Point(x, y), 2, cv::Scalar(color), 2, CV_AA, 0);
		}
		count++;
	}


	gst_buffer_unmap(buffer,&map);
	gst_buffer_unref(buffer);



	/*  sample code below */

	
	GstBuffer *imgBuffer;
	guint buffersize;
	GstFlowReturn ret;
	GstMapInfo info;
	buffersize = frame.cols * frame.rows * frame.channels();
	//g_print("buffersize:%d\n", buffersize);
	imgBuffer = gst_buffer_new_and_alloc(buffersize);
	if (gst_buffer_map(imgBuffer, &info, (GstMapFlags)GST_MAP_WRITE)) {
		memcpy(info.data, frame.data, buffersize);
	gst_buffer_unmap(imgBuffer, &info);
	} 


	//now publish the image into the buffer
	// can the data be replaced?

	/* just push out the incoming buffer without touching it */
	return gst_pad_push(filter->srcpad, imgBuffer);
}


static void gst_lidar_img_stop_processing(GstObject * parent){
	//g_print("%s\n", "gst_lidar_img_stop_processing");
}



static gboolean
gst_lidar_img_src_query(GstPad* pad, GstObject* parent, GstQuery* query)
{
	gboolean ret;
	GstLidarImg *filter;

	filter = GST_LIDARIMG(parent);

	switch (GST_QUERY_TYPE(query)) {
		//case GST_QUERY_POSITION:
		//	/* we should report the current position */
		//	g_print("position query\n");
		//	ret = gst_pad_query_default(pad, parent, query);
		//	break;
		//case GST_QUERY_DURATION:
		//	/* we should report the duration here */
		//	g_print("duration query\n");
		//	ret = gst_pad_query_default(pad, parent, query);
		//	break;
		//case GST_QUERY_CAPS:
		//	/* we should report the supported caps here */
		//	g_print("caps query\n");
		//	GstCaps * caps;
		//	gst_query_parse_caps(query, &caps);
		//	if (!GST_IS_CAPS(caps)){
		//		g_print("caps is not a valid caps\n");
		//	}
		//	else{
		//		g_print("caps size: %d\n", gst_caps_get_size(caps));
		//		for (int i = 0; i < gst_caps_get_size(caps); i++) {
		//			GstStructure *structure = gst_caps_get_structure(caps, i);
		//			char* fields;
		//			gst_structure_foreach(structure, inspectField,NULL);
		//			/*while (fields != NULL){
		//				g_print("field: %s\n", fields);
		//				fields++;
		//			}*/
		//		}
		//	}
		//	ret = gst_pad_query_default(pad, parent, query);
		//	break;
	default:
		/* just call the default handler */
		//g_print("other query\n");
		ret = gst_pad_query_default(pad, parent, query);
		break;
	}
	return ret;
}

