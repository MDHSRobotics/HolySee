# CSee Plugins

This repository contains Team 4141 developped gstreamer image processing (OpenCV) plugins required for computer vision and augmented reality . See [Understanding HolySee](https://github.com/MDHSRobotics/TeamWiki/wiki/Understanding%20HolySee) and the [HolySee project site](https://github.com/MDHSRobotics/HolySee) for more information regarding the overall computer vision solution architecture.

####Types of plugins
This framework comes with 3 types of plugins:

* __ARFilter__ - This type of plugin is used to implement a custom image processing filter suited for augmented reality, like identifying a target and marking it on a view that the operator is watching.
* __CVSink__ - This type of plugin is used to implement a custom computer vision sink.  This type of plugin is best suited for when the image processing is intended to send information directly to the robot but is not intended to be viewed by the operator.  This can be used to enable autonomous functions that are dependent on computer vision.  
* __CVSrc__ - This type of plugin is used to implement a custom computer vision src.  This type of plugin is best suited for when a custom component is needed in order to inject images into the video processing pipeline.  One example if for lidar, where a custom plugin can be used to transform the lidar data into an image that can then be streamed into the pipeline for image processing or viewing by the operator.  
The plugins are generic plug ins which are configurable.  It is generally not necessary to write a plug in, but rather to write a computer vision (OpenCV) filter that is suited for one of these plugins.  

####Creating a Image Processing component
To create a new plug in, start by cloning one of the existing filters, e.g. CircleAR.  Since this is done in c++, you will need a header (.h) file and a code file (.cpp).  It is recommended that, where applicable, GRIP be used to do the initial image processing filter design and to generate sample code for your filter.  Grip generated code can then be copied into and adapted to your new filter.  The gstreamer framework will pick up the appropriate filter based on configration and pipeline specification.

####Adding your Image Processing component to the framework
To add (or register) your plug in to the framework, simple modifications to the FilterManager.cpp files are needed:

* include the header for your filter
* add your component to the FilterManager in the 

see example below:
```
//add includes for your filters here ----------
#include "SquareAR.h"
#include "CircleAR.h"
//---------------------------------------------

void FilterManager::initialize(){
	Filter* filter;

	//add filters here---------------------
	filter = new SquareAR();
	add(filter->getName(), filter);

	filter = new CircleAR();
	add(filter->getName(), filter);
	//-------------------------------------
}
```
####Deploying Updated libraries
When new components are added, it is necessary to recompile the library and to deploy it to the system where it will be used.  Deployment simply entails copying the built library to the appropriate gstreamer folder in the system where it will be used.
   
####Using your Image Processing component
To use your component in an HolySee implemented pipeline, simply update the MSee configuration file with which filter to use for which input source. 
```
# MSee Configuration
# Use this file to define how to identify cameras and other related devices, e.g. lidars
# Also specify image processing components
# AR stands for Augmented Reality filters
# CV stands for Computer Vision sinks
# the argument specifies the name of the component to use

# The format is:
# <instance name>.<device name>.<field> = <value>
#
# intance name - each instance of MSee is given a name.  In this case, this instance is called Tegra.  This is to enable multiple CV co-processors to be added concurrently into a robot.
# device name - each device is given a name.  In this case, three device are identified for this instance.  
# fields - each device can have multiple configuration entries. Each device should have 
#           1) identifier entry.  The identifier entry is used to identify the specific device.  V4l2--ctl is used to identify video devices.  a custom script is used to identify USB devices
#           2) AR entries specify are used to specify which Augmented Reality filter component to use for the specified device
#           3) CV entries specify are used to specify which Computer Vision sink component to use for the specified device

Tegra.tegraCam.identifier = USB2.0 HD UVC WebCam
Tegra.tegraCam.AR = circleAR
Tegra.tegraCam.CV = tegraCamCV

Tegra.zed.identifier = Zebra CAMERA
Tegra.zed.AR = squareAR
Tegra.zed.CV = zedCV

Tegra.lidar.identifier = Chicony_Electronics_Co._Ltd._USB2.0_HD_UVC_WebCam_0x0001
Tegra.lidar.AR = lidarAR
Tegra.lidar.CV = lidarCV```
