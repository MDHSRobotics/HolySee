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

#ifndef __GST_LIDAR_IMG_H__
#define __GST_LIDAR_IMG_H__

#include <string>
#include <gst/gst.h>

G_BEGIN_DECLS

/* #defines don't like whitespacey bits */
#define GST_TYPE_LIDARIMG \
	(gst_lidar_img_get_type())
#define GST_LIDARIMG(obj) \
	(G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_LIDARIMG, GstLidarImg))
#define GST_LIDARIMG_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_LIDARIMG, GstLidarImgClass))
#define GST_IS_LIDARIMG(obj) \
	(G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_LIDARIMG))
#define GST_IS_LIDARIMG_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_LIDARIMG))


typedef struct _GstLidarImg      GstLidarImg;
typedef struct _GstLidarImgClass GstLidarImgClass;

typedef enum {
	STYLE_SIMPLE,
	STYLE_GRADUATED
}PointStyle;

struct _GstLidarImg
{
	GstElement element;

	GstPad *sinkpad, *srcpad;

	gboolean silent;

	int width;
	int height;
	std::string format;
	PointStyle style;

};

struct _GstLidarImgClass
{
	GstElementClass parent_class;
};

GType gst_lidar_img_get_type(void);

G_END_DECLS

#endif /* __GST_LIDAR_IMG_H__ */
