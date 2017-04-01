#include "gstarfilter.h"
#include "gstlidarsrc.h"
#include "gstlidarimg.h"

static gboolean
plugin_init(GstPlugin * plugin)
{
	//g_print("%s\n", "plugin_init");
	return 
		gst_element_register(plugin, "arfilter",
		GST_RANK_NONE, GST_TYPE_ARFILTER);
		gst_element_register(plugin, "lidarsrc",
		GST_RANK_NONE, GST_TYPE_LIDAR_SRC) &&
		gst_element_register(plugin, "lidarimg",
		GST_RANK_NONE, GST_TYPE_LIDARIMG);
}



/* PACKAGE: this is usually set by autotools depending on some _INIT macro
* in configure.ac and then written into and defined in config.h, but we can
* just set it ourselves here in case someone doesn't use autotools to
* compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
*/
#ifndef PACKAGE
#define PACKAGE "csee"
#endif
#ifndef VERSION
#define VERSION "0.1"
#endif

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
	GST_VERSION_MINOR,
	csee,
	"csee",
	plugin_init, VERSION,
	"LGPL",
	"GStreamer",
	"http://gstreamer.net/"
	)
