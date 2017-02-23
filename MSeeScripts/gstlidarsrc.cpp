#include "stdafx.h"
/* GStreamer
* Copyright (C) <2017> Martin Smith <msmith92663@gmail.com>
*  @author: Martin Smith <msmith92663@gmail.com>
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
* Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/
/**
* SECTION:element-lidarsrc
*
* Source element to stream data from a RP Lidar A1 device into a gstreamer 1.0 pipeline.
* adapted from https://github.com/GStreamer/gst-plugins-bad/blob/master/sys/shm
*
* <refsect2>
* <title>Example launch lines</title>
* |[
* gst-launch-1.0 --gst-plugin-path=C:\projects\lidarsrc\x64\Release lidarsrc device=/dev/ttyUSB0 ! lidarimg ! video/x-raw, format=GRAY8, framerate=5/1, widht=640, height=480 ! videoconvert ! autovideosink
* ]| Stream data from lidar device.
* </refsect2>
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstlidarsrc.h"

#include <gst/gst.h>

#include <string.h>
#include <stdio.h>

/* signals */
enum
{
	LAST_SIGNAL
};

/* properties */
enum
{
	PROP_0,
	PROP_DEVICE,
	PROP_IS_LIVE,
	PROP_IS_SIMULATION
};

struct GstLidarBuffer
{
	unsigned char *buf;
	int bufferSize = 0;
};

GST_DEBUG_CATEGORY_STATIC(lidarsrc_debug);
#define GST_CAT_DEFAULT lidarsrc_debug

static GstStaticPadTemplate srctemplate = GST_STATIC_PAD_TEMPLATE("src",
	GST_PAD_SRC,
	GST_PAD_ALWAYS,
	GST_STATIC_CAPS_ANY);

#define gst_lidar_src_parent_class parent_class
G_DEFINE_TYPE(GstLidarSrc, gst_lidar_src, GST_TYPE_PUSH_SRC);

static void gst_lidar_src_set_property(GObject * object, guint prop_id,
	const GValue * value, GParamSpec * pspec);
static void gst_lidar_src_get_property(GObject * object, guint prop_id,
	GValue * value, GParamSpec * pspec);
static void gst_lidar_src_finalize(GObject * object);
static gboolean gst_lidar_src_start(GstBaseSrc * bsrc);
static gboolean gst_lidar_src_stop(GstBaseSrc * bsrc);
static GstFlowReturn gst_lidar_src_create(GstPushSrc * psrc,
	GstBuffer ** outbuf);
static gboolean gst_lidar_src_unlock(GstBaseSrc * bsrc);
static gboolean gst_lidar_src_unlock_stop(GstBaseSrc * bsrc);
static GstStateChangeReturn gst_lidar_src_change_state(GstElement * element,
	GstStateChange transition);


static void
gst_lidar_src_class_init(GstLidarSrcClass * klass)
{
	//g_print("gst_lidar_src_class_init\n");
	GObjectClass *gobject_class;
	GstElementClass *gstelement_class;
	GstBaseSrcClass *gstbasesrc_class;
	GstPushSrcClass *gstpush_src_class;

	gobject_class = (GObjectClass *)klass;
	gstelement_class = (GstElementClass *)klass;
	gstbasesrc_class = (GstBaseSrcClass *)klass;
	gstpush_src_class = (GstPushSrcClass *)klass;

	gobject_class->set_property = gst_lidar_src_set_property;
	gobject_class->get_property = gst_lidar_src_get_property;
	gobject_class->finalize = gst_lidar_src_finalize;

	gstelement_class->change_state = gst_lidar_src_change_state;

	gstbasesrc_class->start = GST_DEBUG_FUNCPTR(gst_lidar_src_start);
	gstbasesrc_class->stop = GST_DEBUG_FUNCPTR(gst_lidar_src_stop);
	gstbasesrc_class->unlock = GST_DEBUG_FUNCPTR(gst_lidar_src_unlock);
	gstbasesrc_class->unlock_stop = GST_DEBUG_FUNCPTR(gst_lidar_src_unlock_stop);

	gstpush_src_class->create = gst_lidar_src_create;

	g_object_class_install_property(gobject_class, PROP_DEVICE,
		g_param_spec_string("device",
		"Device path",
		"The device path for the lidar, , typically /dev/ttyUSB0",
		NULL, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

	g_object_class_install_property(gobject_class, PROP_IS_LIVE,
		g_param_spec_boolean("is-live", "Is this a live source",
		"True if the element cannot produce data in PAUSED", TRUE,
		(GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

	g_object_class_install_property(gobject_class, PROP_IS_SIMULATION,
		g_param_spec_boolean("simulate", "Is this a simulation",
		"True if the the source should simulate a device", FALSE,
		(GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

	gst_element_class_add_static_pad_template(gstelement_class, &srctemplate);

	gst_element_class_set_static_metadata(gstelement_class,
		"Lidar Source",
		"Source",
		"Receive data from a RP Lidar A1 device",
		"Martin Smith<mamith92663@gmail.com>");

	GST_DEBUG_CATEGORY_INIT(lidarsrc_debug, "lidarsrc", 0, "Lidar Source");
}

static void
gst_lidar_src_init(GstLidarSrc * self)
{
	//g_print("gst_lidar_src_init\n");
	//self->poll = gst_poll_new(TRUE);
	//gst_poll_fd_init(&self->pollfd);
	////g_print("allocating LidarDevice\n");
}

static void
gst_lidar_src_finalize(GObject * object)
{
	GstLidarSrc *self = GST_LIDAR_SRC(object);

	//gst_poll_free(self->poll);
	//g_free(self->socket_path);

	G_OBJECT_CLASS(parent_class)->finalize(object);
}


static void
gst_lidar_src_set_property(GObject * object, guint prop_id,
const GValue * value, GParamSpec * pspec)
{
	GstLidarSrc *self = GST_LIDAR_SRC(object);

	switch (prop_id) {
	case PROP_DEVICE:
		GST_OBJECT_LOCK(object);
		self->device = g_value_dup_string(value);
		GST_OBJECT_UNLOCK(object);
		break;
	case PROP_IS_LIVE:
		gst_base_src_set_live(GST_BASE_SRC(object),
			g_value_get_boolean(value));
		break;
	case PROP_IS_SIMULATION:
		GST_OBJECT_LOCK(object);
		self->isSimulation = g_value_get_boolean(value);
		GST_OBJECT_UNLOCK(object);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
gst_lidar_src_get_property(GObject * object, guint prop_id,
GValue * value, GParamSpec * pspec)
{
	GstLidarSrc *self = GST_LIDAR_SRC(object);

	switch (prop_id) {
	case PROP_DEVICE:
		g_value_set_string(value, self->device);
		break;
	case PROP_IS_LIVE:
		g_value_set_boolean(value, gst_base_src_is_live(GST_BASE_SRC(object)));
		break;
	case PROP_IS_SIMULATION:
		g_value_set_boolean(value, self->isSimulation);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static gboolean
gst_lidar_src_start_reading(GstLidarSrc * self)
{
	//g_print("gst_lidar_src_start_reading\n");

	if (!self->device) {
		GST_ELEMENT_ERROR(self, RESOURCE, NOT_FOUND,
			("No device specified for lidar."), (NULL));
		return FALSE;
	}
	self->lidar = new LidarDevice(self->device, self->isSimulation);
	return TRUE;
}

static void
gst_lidar_src_stop_reading(GstLidarSrc * self)
{
	//g_print("gst_lidar_src_stop_reading\n");

	GST_DEBUG_OBJECT(self, "Stopping %p", self);
	if (self->lidar != NULL){
		delete 	self->lidar;
		self->lidar = NULL;
		//g_print("freeing up lidar resources");
	}

	//if (self->pipe) {
	//	gst_shm_pipe_dec(self->pipe);
	//	self->pipe = NULL;

	//	gst_poll_remove_fd(self->poll, &self->pollfd);
	//}

	//gst_poll_fd_init(&self->pollfd);
	//gst_poll_set_flushing(self->poll, TRUE);
}

static gboolean
gst_lidar_src_start(GstBaseSrc * bsrc)
{
	//g_print("gst_lidar_src_start\n");
	//if (gst_base_src_is_live(bsrc))
	//	return TRUE;
	//else
	return gst_lidar_src_start_reading(GST_LIDAR_SRC(bsrc));
}

static gboolean
gst_lidar_src_stop(GstBaseSrc * bsrc)
{
	//g_print("gst_lidar_src_stop\n");
	//if (!gst_base_src_is_live(bsrc))
	//	gst_lidar_src_stop_reading(GST_LIDAR_SRC(bsrc));

	return TRUE;
}


static void
free_buffer(gpointer data)
{
	struct GstLidarBuffer *glb = (GstLidarBuffer *)data;
	g_slice_free(struct GstLidarBuffer, glb);
	////g_print("frame buffer freed\n");
}


int writeFrame(Frame& frame, unsigned char * buffer, int bufferSize){
	//unsigned char * buffer = (unsigned char *)malloc(size);
	unsigned char * data = NULL;
	////g_print("data %p, buffer %p, size %d\n", data, buffer, size);
	//for (int i = 0; i < size; i++){
	//	////g_print("i=%d\n", i);
	//	*(buffer + i) = *(data + i);
	//}
	// the above may fail due to padding.  
	//test that the allocated memory is writeable for the specified size
	//for (int i = 0; i < size; i++){
	//	////g_print("i=%d\n", i);
	//	*(buffer + i) = 0x5A;
	//}
	//confirmed, it's due to struct not guaranteed to have contiguous memory
	int bytesWritten = 0;
	//write header
	////g_print("header: \n");
	data = reinterpret_cast<unsigned char*>(&(frame.header));
	for (int i = 0; i < sizeof frame.header; i++){
		*(buffer + bytesWritten) = *(data + i);
		////g_print("%02x",*(buffer+bytesWritten));
		bytesWritten++;
		//if (bytesWritten % 2 == 0) //g_print(" ");
	}
	////g_print("\nreadings: \n");
	////g_print("tranferring %d readings \n", frame.header.count);
	int readingSize = sizeof frame.readings[0];
	for (int j = 0; j < frame.header.count; j++){
		data = reinterpret_cast<unsigned char*>(&(frame.readings[j]));
		//if (j == 0){
		//	//g_print("reading size:%d, reading[angle:%f, distance:%f, quality:0x%02x, sync:0x%02x] \n", sizeof frame.readings[j], frame.readings[j].angle, frame.readings[j].distance, frame.readings[j].qualityFlag, frame.readings[j].syncFlag);
		//}
		for (int i = 0; i < readingSize; i++){
			*(buffer + bytesWritten) = *(data + i);
			//if (j == 0) //g_print("%02x", *(buffer + bytesWritten));
			bytesWritten++;
			//if (j == 0) if (bytesWritten % 2 == 0) //g_print(" ");
		}
		if (j == 0){
			////g_print("\n");
		}
	}
	//	//g_print("wrote %d bytes\n", bytesWritten);
	return bytesWritten;
}

static GstFlowReturn
gst_lidar_src_create(GstPushSrc * psrc, GstBuffer ** outbuf)
{
	GstLidarSrc *self = GST_LIDAR_SRC(psrc);
	struct GstLidarBuffer *glb;
	glb = g_slice_new0(struct GstLidarBuffer);
	////g_print("gst_lidar_src_create\n");

	Frame& frame = self->lidar->read();
	int bufferSize = sizeof frame.readings[0] * frame.header.count + sizeof frame.header;
	////g_print("frame size: %d, header size: %d, readings size: %d, readings count:%d\n", bufferSize, sizeof frame.header, sizeof frame.readings[0], frame.header.count);
	unsigned char * buffer = (unsigned char *)malloc(bufferSize);
	int bytesWritten = writeFrame(frame, buffer, bufferSize);

	////g_print("Got buffer %p of size %d\n", buffer, bufferSize);
	glb->buf = buffer;

	*outbuf = gst_buffer_new_wrapped_full(GST_MEMORY_FLAG_READONLY,
		buffer, bufferSize, 0, bufferSize, glb, free_buffer);

	return GST_FLOW_OK;
}

static GstStateChangeReturn
gst_lidar_src_change_state(GstElement * element, GstStateChange transition)
{
	//g_print("gst_lidar_src_change_state\n");

	GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
	GstLidarSrc *self = GST_LIDAR_SRC(element);

	switch (transition) {
	case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
		//g_print("GST_STATE_CHANGE_PAUSED_TO_PLAYING\n");
		if (gst_base_src_is_live(GST_BASE_SRC(element)))
		if (!gst_lidar_src_start_reading(self))
			return GST_STATE_CHANGE_FAILURE;
	default:
		break;
	}

	ret = GST_ELEMENT_CLASS(parent_class)->change_state(element, transition);

	if (ret == GST_STATE_CHANGE_FAILURE)
		return ret;

	//g_print("!GST_STATE_CHANGE_FAILURE\n");
	switch (transition) {
	case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
		//g_print("GST_STATE_CHANGE_PLAYING_TO_PAUSED\n");
		if (gst_base_src_is_live(GST_BASE_SRC(element)))
			gst_lidar_src_stop_reading(self);
	default:
		break;
	}
	//g_print("GST_STATE_CHANGE done\n");

	return ret;
}

static gboolean
gst_lidar_src_unlock(GstBaseSrc * bsrc)
{
	//g_print("gst_lidar_src_unlock\n");

	GstLidarSrc *self = GST_LIDAR_SRC(bsrc);

	self->unlocked = TRUE;

	return TRUE;
}

static gboolean
gst_lidar_src_unlock_stop(GstBaseSrc * bsrc)
{
	//g_print("gst_lidar_src_unlock_stop\n");

	GstLidarSrc *self = GST_LIDAR_SRC(bsrc);

	self->unlocked = FALSE;

	return TRUE;
}

