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

#ifndef __GST_LIDAR_SRC_H__
#define __GST_LIDAR_SRC_H__

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>
#include <gst/base/gstbasesrc.h>
#include "LidarDevice.h"


G_BEGIN_DECLS
#define GST_TYPE_LIDAR_SRC \
	(gst_lidar_src_get_type())
#define GST_LIDAR_SRC(obj) \
	(G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_LIDAR_SRC, GstLidarSrc))
#define gst_lidar_src_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_LIDAR_SRC, GstLidarSrcClass))
#define GST_IS_LIDAR_SRC(obj) \
	(G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_LIDAR_SRC))
#define GST_IS_SHM_SRC_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_LIDAR_SRC))
typedef struct _GstLidarSrc GstLidarSrc;
typedef struct _GstLidarSrcClass GstLidarSrcClass;

struct _GstLidarSrc
{
	GstPushSrc element;

	gchar *device = NULL;
	bool isSimulation;

	LidarDevice *lidar = NULL;

//	GstPoll *poll;
//	GstPollFD pollfd;

	GstFlowReturn flow_return;
	gboolean unlocked;
};

struct _GstLidarSrcClass
{
	GstPushSrcClass parent_class;
};

GType gst_lidar_src_get_type(void);

G_END_DECLS
#endif /* __GST_LIDAR_SRC_H__ */